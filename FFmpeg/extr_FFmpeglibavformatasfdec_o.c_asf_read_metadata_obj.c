#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint16_t ;
struct TYPE_9__ {int /*<<< orphan*/  offset; TYPE_1__* asf_sd; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pb; TYPE_3__* priv_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  asf_met; } ;
typedef  int /*<<< orphan*/  GUIDParseTable ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ ASFContext ;

/* Variables and functions */
 int ASF_MAX_STREAMS ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  align_position (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int asf_store_aspect_ratio (TYPE_2__*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * av_malloc (int) ; 
 int /*<<< orphan*/  avio_get_str16le (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int avio_rl16 (int /*<<< orphan*/ *) ; 
 int avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rl64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int process_metadata (TYPE_2__*,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int asf_read_metadata_obj(AVFormatContext *s, const GUIDParseTable *g)
{
    ASFContext *asf   = s->priv_data;
    AVIOContext *pb   = s->pb;
    uint64_t size     = avio_rl64(pb);
    uint16_t nb_recs  = avio_rl16(pb); // number of records in the Description Records list
    int i, ret;

    for (i = 0; i < nb_recs; i++) {
        uint16_t name_len, buflen, type, val_len, st_num;
        uint8_t *name = NULL;

        avio_skip(pb, 2); // skip reserved field
        st_num   = avio_rl16(pb);
        name_len = avio_rl16(pb);
        buflen   = 2 * name_len + 1;
        if (!name_len)
            break;
        type     = avio_rl16(pb);
        val_len  = avio_rl32(pb);
        name     = av_malloc(buflen);
        if (!name)
            return AVERROR(ENOMEM);
        avio_get_str16le(pb, name_len, name,
                         buflen);
        if (!strcmp(name, "AspectRatioX") || !strcmp(name, "AspectRatioY")) {
            ret = asf_store_aspect_ratio(s, st_num, name, type);
            if (ret < 0) {
                av_freep(&name);
                break;
            }
        } else {
            if (st_num < ASF_MAX_STREAMS) {
                if ((ret = process_metadata(s, name, name_len, val_len, type,
                                            &asf->asf_sd[st_num].asf_met)) < 0) {
                    av_freep(&name);
                    break;
                }
            }
        }
        av_freep(&name);
    }

    align_position(pb, asf->offset, size);
    return 0;
}