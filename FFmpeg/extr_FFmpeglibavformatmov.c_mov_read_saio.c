#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
struct TYPE_29__ {scalar_t__ eof_reached; } ;
struct TYPE_25__ {scalar_t__ base_data_offset; } ;
struct TYPE_24__ {scalar_t__ current; } ;
struct TYPE_28__ {int /*<<< orphan*/  fc; TYPE_4__ fragment; TYPE_3__ frag_index; } ;
struct TYPE_27__ {int auxiliary_offsets_count; scalar_t__ auxiliary_info_sample_count; void** auxiliary_offsets; scalar_t__ nb_encrypted_samples; } ;
struct TYPE_23__ {TYPE_1__* default_encrypted_sample; } ;
struct TYPE_26__ {TYPE_2__ cenc; } ;
struct TYPE_22__ {unsigned int scheme; } ;
typedef  TYPE_5__ MOVStreamContext ;
typedef  TYPE_6__ MOVEncryptionIndex ;
typedef  TYPE_7__ MOVContext ;
typedef  int /*<<< orphan*/  MOVAtom ;
typedef  TYPE_8__ AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMAX (int,int) ; 
 unsigned int FFMIN (int /*<<< orphan*/ ,unsigned int) ; 
 int INT_MAX ; 
 unsigned int MKBETAG (char,char,char,char) ; 
 void** av_fast_realloc (void**,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  av_freep (void***) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 unsigned int avio_r8 (TYPE_8__*) ; 
 int avio_rb24 (TYPE_8__*) ; 
 void* avio_rb32 (TYPE_8__*) ; 
 void* avio_rb64 (TYPE_8__*) ; 
 int get_current_encryption_info (TYPE_7__*,TYPE_6__**,TYPE_5__**) ; 
 int mov_parse_auxiliary_info (TYPE_7__*,TYPE_5__*,TYPE_8__*,TYPE_6__*) ; 

__attribute__((used)) static int mov_read_saio(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    uint64_t *auxiliary_offsets;
    MOVEncryptionIndex *encryption_index;
    MOVStreamContext *sc;
    int i, ret;
    unsigned int version, entry_count, aux_info_type, aux_info_param;
    unsigned int alloc_size = 0;

    ret = get_current_encryption_info(c, &encryption_index, &sc);
    if (ret != 1)
        return ret;

    if (encryption_index->nb_encrypted_samples) {
        // This can happen if we have both saio/saiz and senc atoms.
        av_log(c->fc, AV_LOG_DEBUG, "Ignoring duplicate encryption info in saio\n");
        return 0;
    }

    if (encryption_index->auxiliary_offsets_count) {
        av_log(c->fc, AV_LOG_ERROR, "Duplicate saio atom\n");
        return AVERROR_INVALIDDATA;
    }

    version = avio_r8(pb); /* version */
    if (avio_rb24(pb) & 0x01) {  /* flags */
        aux_info_type = avio_rb32(pb);
        aux_info_param = avio_rb32(pb);
        if (sc->cenc.default_encrypted_sample) {
            if (aux_info_type != sc->cenc.default_encrypted_sample->scheme) {
                av_log(c->fc, AV_LOG_DEBUG, "Ignoring saio box with non-zero aux_info_type\n");
                return 0;
            }
            if (aux_info_param != 0) {
                av_log(c->fc, AV_LOG_DEBUG, "Ignoring saio box with non-zero aux_info_type_parameter\n");
                return 0;
            }
        } else {
            // Didn't see 'schm' or 'tenc', so this isn't encrypted.
            if ((aux_info_type == MKBETAG('c','e','n','c') ||
                 aux_info_type == MKBETAG('c','e','n','s') ||
                 aux_info_type == MKBETAG('c','b','c','1') ||
                 aux_info_type == MKBETAG('c','b','c','s')) &&
                aux_info_param == 0) {
                av_log(c->fc, AV_LOG_ERROR, "Saw encrypted saio without schm/tenc\n");
                return AVERROR_INVALIDDATA;
            } else {
                return 0;
            }
        }
    } else if (!sc->cenc.default_encrypted_sample) {
        // Didn't see 'schm' or 'tenc', so this isn't encrypted.
        return 0;
    }

    entry_count = avio_rb32(pb);
    if (entry_count >= INT_MAX / sizeof(*auxiliary_offsets))
        return AVERROR(ENOMEM);

    for (i = 0; i < entry_count && !pb->eof_reached; i++) {
        unsigned int min_offsets = FFMIN(FFMAX(i + 1, 1024), entry_count);
        auxiliary_offsets = av_fast_realloc(
            encryption_index->auxiliary_offsets, &alloc_size,
            min_offsets * sizeof(*auxiliary_offsets));
        if (!auxiliary_offsets) {
            av_freep(&encryption_index->auxiliary_offsets);
            return AVERROR(ENOMEM);
        }
        encryption_index->auxiliary_offsets = auxiliary_offsets;

        if (version == 0) {
            encryption_index->auxiliary_offsets[i] = avio_rb32(pb);
        } else {
            encryption_index->auxiliary_offsets[i] = avio_rb64(pb);
        }
        if (c->frag_index.current >= 0) {
            encryption_index->auxiliary_offsets[i] += c->fragment.base_data_offset;
        }
    }

    if (pb->eof_reached) {
        av_log(c->fc, AV_LOG_ERROR, "Hit EOF while reading saio\n");
        av_freep(&encryption_index->auxiliary_offsets);
        return AVERROR_INVALIDDATA;
    }

    encryption_index->auxiliary_offsets_count = entry_count;

    if (encryption_index->auxiliary_info_sample_count) {
        return mov_parse_auxiliary_info(c, sc, pb, encryption_index);
    }

    return 0;
}