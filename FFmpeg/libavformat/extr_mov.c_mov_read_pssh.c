#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_19__ {unsigned int num_key_ids; unsigned int data_size; struct TYPE_19__* next; int /*<<< orphan*/ * data; int /*<<< orphan*/ ** key_ids; int /*<<< orphan*/ * system_id; } ;
struct TYPE_18__ {scalar_t__ eof_reached; } ;
struct TYPE_17__ {TYPE_11__* fc; } ;
struct TYPE_16__ {int nb_streams; int /*<<< orphan*/ ** streams; } ;
typedef  TYPE_1__ MOVContext ;
typedef  int /*<<< orphan*/  MOVAtom ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  TYPE_2__ AVIOContext ;
typedef  TYPE_3__ AVEncryptionInitInfo ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_DATA_ENCRYPTION_INIT_INFO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMAX (unsigned int,int) ; 
 unsigned int FFMIN (int /*<<< orphan*/ ,unsigned int) ; 
 int INT_MAX ; 
 int /*<<< orphan*/ * av_encryption_init_info_add_side_data (TYPE_3__*,size_t*) ; 
 TYPE_3__* av_encryption_init_info_alloc (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_encryption_init_info_free (TYPE_3__*) ; 
 TYPE_3__* av_encryption_init_info_get_side_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ ** av_fast_realloc (int /*<<< orphan*/ **,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_log (TYPE_11__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * av_mallocz (int) ; 
 int av_stream_add_side_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * av_stream_get_side_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 unsigned int avio_r8 (TYPE_2__*) ; 
 int /*<<< orphan*/  avio_rb24 (TYPE_2__*) ; 
 unsigned int avio_rb32 (TYPE_2__*) ; 
 int avio_read (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int mov_try_read_block (TYPE_2__*,unsigned int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int mov_read_pssh(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    AVEncryptionInitInfo *info, *old_init_info;
    uint8_t **key_ids;
    AVStream *st;
    uint8_t *side_data, *extra_data, *old_side_data;
    size_t side_data_size;
    int ret = 0, old_side_data_size;
    unsigned int version, kid_count, extra_data_size, alloc_size = 0;

    if (c->fc->nb_streams < 1)
        return 0;
    st = c->fc->streams[c->fc->nb_streams-1];

    version = avio_r8(pb); /* version */
    avio_rb24(pb);  /* flags */

    info = av_encryption_init_info_alloc(/* system_id_size */ 16, /* num_key_ids */ 0,
                                         /* key_id_size */ 16, /* data_size */ 0);
    if (!info)
        return AVERROR(ENOMEM);

    if (avio_read(pb, info->system_id, 16) != 16) {
        av_log(c->fc, AV_LOG_ERROR, "Failed to read the system id\n");
        ret = AVERROR_INVALIDDATA;
        goto finish;
    }

    if (version > 0) {
        kid_count = avio_rb32(pb);
        if (kid_count >= INT_MAX / sizeof(*key_ids))
            return AVERROR(ENOMEM);

        for (unsigned int i = 0; i < kid_count && !pb->eof_reached; i++) {
            unsigned int min_kid_count = FFMIN(FFMAX(i + 1, 1024), kid_count);
            key_ids = av_fast_realloc(info->key_ids, &alloc_size,
                                      min_kid_count * sizeof(*key_ids));
            if (!key_ids) {
                ret = AVERROR(ENOMEM);
                goto finish;
            }
            info->key_ids = key_ids;

            info->key_ids[i] = av_mallocz(16);
            if (!info->key_ids[i]) {
                ret = AVERROR(ENOMEM);
                goto finish;
            }
            info->num_key_ids = i + 1;

            if (avio_read(pb, info->key_ids[i], 16) != 16) {
                av_log(c->fc, AV_LOG_ERROR, "Failed to read the key id\n");
                ret = AVERROR_INVALIDDATA;
                goto finish;
            }
        }

        if (pb->eof_reached) {
            av_log(c->fc, AV_LOG_ERROR, "Hit EOF while reading pssh\n");
            ret = AVERROR_INVALIDDATA;
            goto finish;
        }
    }

    extra_data_size = avio_rb32(pb);
    ret = mov_try_read_block(pb, extra_data_size, &extra_data);
    if (ret < 0)
        goto finish;

    av_freep(&info->data);  // malloc(0) may still allocate something.
    info->data = extra_data;
    info->data_size = extra_data_size;

    // If there is existing initialization data, append to the list.
    old_side_data = av_stream_get_side_data(st, AV_PKT_DATA_ENCRYPTION_INIT_INFO, &old_side_data_size);
    if (old_side_data) {
        old_init_info = av_encryption_init_info_get_side_data(old_side_data, old_side_data_size);
        if (old_init_info) {
            // Append to the end of the list.
            for (AVEncryptionInitInfo *cur = old_init_info;; cur = cur->next) {
                if (!cur->next) {
                    cur->next = info;
                    break;
                }
            }
            info = old_init_info;
        } else {
            // Assume existing side-data will be valid, so the only error we could get is OOM.
            ret = AVERROR(ENOMEM);
            goto finish;
        }
    }

    side_data = av_encryption_init_info_add_side_data(info, &side_data_size);
    if (!side_data) {
        ret = AVERROR(ENOMEM);
        goto finish;
    }
    ret = av_stream_add_side_data(st, AV_PKT_DATA_ENCRYPTION_INIT_INFO,
                                  side_data, side_data_size);
    if (ret < 0)
        av_free(side_data);

finish:
    av_encryption_init_info_free(info);
    return ret;
}