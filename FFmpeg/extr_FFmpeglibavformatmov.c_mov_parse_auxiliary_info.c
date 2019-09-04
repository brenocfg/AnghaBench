#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_19__ {int seekable; scalar_t__ eof_reached; } ;
struct TYPE_18__ {int /*<<< orphan*/  fc; } ;
struct TYPE_17__ {size_t nb_encrypted_samples; size_t auxiliary_info_sample_count; int auxiliary_offsets_count; scalar_t__* auxiliary_offsets; size_t auxiliary_info_default_size; size_t* auxiliary_info_sizes; int /*<<< orphan*/ ** encrypted_samples; } ;
struct TYPE_15__ {size_t per_sample_iv_size; } ;
struct TYPE_16__ {TYPE_1__ cenc; } ;
typedef  TYPE_2__ MOVStreamContext ;
typedef  TYPE_3__ MOVEncryptionIndex ;
typedef  TYPE_4__ MOVContext ;
typedef  TYPE_5__ AVIOContext ;
typedef  int /*<<< orphan*/  AVEncryptionInfo ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int AVIO_SEEKABLE_NORMAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMAX (size_t,int) ; 
 unsigned int FFMIN (int /*<<< orphan*/ ,size_t) ; 
 int INT_MAX ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_encryption_info_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** av_fast_realloc (int /*<<< orphan*/ **,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ ***) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ avio_seek (TYPE_5__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_tell (TYPE_5__*) ; 
 int mov_read_sample_encryption_info (TYPE_4__*,TYPE_5__*,TYPE_2__*,int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static int mov_parse_auxiliary_info(MOVContext *c, MOVStreamContext *sc, AVIOContext *pb, MOVEncryptionIndex *encryption_index)
{
    AVEncryptionInfo **sample, **encrypted_samples;
    int64_t prev_pos;
    size_t sample_count, sample_info_size, i;
    int ret = 0;
    unsigned int alloc_size = 0;

    if (encryption_index->nb_encrypted_samples)
        return 0;
    sample_count = encryption_index->auxiliary_info_sample_count;
    if (encryption_index->auxiliary_offsets_count != 1) {
        av_log(c->fc, AV_LOG_ERROR, "Multiple auxiliary info chunks are not supported\n");
        return AVERROR_PATCHWELCOME;
    }
    if (sample_count >= INT_MAX / sizeof(*encrypted_samples))
        return AVERROR(ENOMEM);

    prev_pos = avio_tell(pb);
    if (!(pb->seekable & AVIO_SEEKABLE_NORMAL) ||
        avio_seek(pb, encryption_index->auxiliary_offsets[0], SEEK_SET) != encryption_index->auxiliary_offsets[0]) {
        av_log(c->fc, AV_LOG_INFO, "Failed to seek for auxiliary info, will only parse senc atoms for encryption info\n");
        goto finish;
    }

    for (i = 0; i < sample_count && !pb->eof_reached; i++) {
        unsigned int min_samples = FFMIN(FFMAX(i + 1, 1024 * 1024), sample_count);
        encrypted_samples = av_fast_realloc(encryption_index->encrypted_samples, &alloc_size,
                                            min_samples * sizeof(*encrypted_samples));
        if (!encrypted_samples) {
            ret = AVERROR(ENOMEM);
            goto finish;
        }
        encryption_index->encrypted_samples = encrypted_samples;

        sample = &encryption_index->encrypted_samples[i];
        sample_info_size = encryption_index->auxiliary_info_default_size
                               ? encryption_index->auxiliary_info_default_size
                               : encryption_index->auxiliary_info_sizes[i];

        ret = mov_read_sample_encryption_info(c, pb, sc, sample, sample_info_size > sc->cenc.per_sample_iv_size);
        if (ret < 0)
            goto finish;
    }
    if (pb->eof_reached) {
        av_log(c->fc, AV_LOG_ERROR, "Hit EOF while reading auxiliary info\n");
        ret = AVERROR_INVALIDDATA;
    } else {
        encryption_index->nb_encrypted_samples = sample_count;
    }

finish:
    avio_seek(pb, prev_pos, SEEK_SET);
    if (ret < 0) {
        for (; i > 0; i--) {
            av_encryption_info_free(encryption_index->encrypted_samples[i - 1]);
        }
        av_freep(&encryption_index->encrypted_samples);
    }
    return ret;
}