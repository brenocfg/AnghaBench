#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  ff_asf_guid ;
struct TYPE_33__ {scalar_t__ offset; scalar_t__ unknown_offset; int is_header; int b_flags; int nb_streams; TYPE_4__* asf_sd; TYPE_1__** asf_st; int /*<<< orphan*/  first_packet_offset; scalar_t__ data_reached; scalar_t__ is_simple_index; scalar_t__ preroll; } ;
struct TYPE_32__ {TYPE_6__** streams; TYPE_7__* pb; TYPE_9__* priv_data; } ;
struct TYPE_31__ {int seekable; } ;
struct TYPE_26__ {scalar_t__ num; scalar_t__ den; } ;
struct TYPE_30__ {TYPE_2__ sample_aspect_ratio; int /*<<< orphan*/  metadata; } ;
struct TYPE_29__ {int (* read_object ) (TYPE_8__*,TYPE_5__ const*) ;} ;
struct TYPE_27__ {scalar_t__ num; scalar_t__ den; } ;
struct TYPE_28__ {char* langs; TYPE_3__ aspect_ratio; int /*<<< orphan*/  asf_met; } ;
struct TYPE_25__ {size_t lang_idx; size_t index; } ;
typedef  TYPE_5__ GUIDParseTable ;
typedef  TYPE_6__ AVStream ;
typedef  TYPE_7__ AVIOContext ;
typedef  TYPE_8__ AVFormatContext ;
typedef  TYPE_9__ ASFContext ;

/* Variables and functions */
 int ASF_FLAG_BROADCAST ; 
 int ASF_MAX_STREAMS ; 
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int AVIO_SEEKABLE_NORMAL ; 
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  align_position (TYPE_7__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asf_read_close (TYPE_8__*) ; 
 int /*<<< orphan*/  av_dict_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_8__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_rl64 (TYPE_7__*) ; 
 int /*<<< orphan*/  avio_seek (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (TYPE_7__*,int) ; 
 scalar_t__ avio_tell (TYPE_7__*) ; 
 int /*<<< orphan*/  ff_asf_header ; 
 int ff_get_guid (TYPE_7__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ff_guidcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* find_guid (int /*<<< orphan*/ ) ; 
 TYPE_6__* find_stream (TYPE_8__*,int) ; 
 int /*<<< orphan*/  set_language (TYPE_8__*,char const*,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_8__*,TYPE_5__ const*) ; 

__attribute__((used)) static int asf_read_header(AVFormatContext *s)
{
    ASFContext *asf         = s->priv_data;
    AVIOContext *pb         = s->pb;
    const GUIDParseTable *g = NULL;
    ff_asf_guid guid;
    int i, ret;
    uint64_t size;

    asf->preroll         = 0;
    asf->is_simple_index = 0;
    ff_get_guid(pb, &guid);
    if (ff_guidcmp(&guid, &ff_asf_header))
        return AVERROR_INVALIDDATA;
    avio_skip(pb, 8); // skip header object size
    avio_skip(pb, 6); // skip number of header objects and 2 reserved bytes
    asf->data_reached = 0;

    /* 1  is here instead of pb->eof_reached because (when not streaming), Data are skipped
     * for the first time,
     * Index object is processed and got eof and then seeking back to the Data is performed.
     */
    while (1) {
        // for the cases when object size is invalid
        if (avio_tell(pb) == asf->offset)
            break;
        asf->offset = avio_tell(pb);
        if ((ret = ff_get_guid(pb, &guid)) < 0) {
            if (ret == AVERROR_EOF && asf->data_reached)
                break;
            else
                goto failed;
        }
        g = find_guid(guid);
        if (g) {
            asf->unknown_offset = asf->offset;
            asf->is_header = 1;
            if ((ret = g->read_object(s, g)) < 0)
                goto failed;
        } else {
            size = avio_rl64(pb);
            align_position(pb, asf->offset, size);
        }
        if (asf->data_reached &&
            (!(pb->seekable & AVIO_SEEKABLE_NORMAL) ||
             (asf->b_flags & ASF_FLAG_BROADCAST)))
            break;
    }

    if (!asf->data_reached) {
        av_log(s, AV_LOG_ERROR, "Data Object was not found.\n");
        ret = AVERROR_INVALIDDATA;
        goto failed;
    }
    if (pb->seekable & AVIO_SEEKABLE_NORMAL)
        avio_seek(pb, asf->first_packet_offset, SEEK_SET);

    for (i = 0; i < asf->nb_streams; i++) {
        const char *rfc1766 = asf->asf_sd[asf->asf_st[i]->lang_idx].langs;
        AVStream *st        = s->streams[asf->asf_st[i]->index];
        set_language(s, rfc1766, &st->metadata);
    }

    for (i = 0; i < ASF_MAX_STREAMS; i++) {
        AVStream *st = NULL;

        st = find_stream(s, i);
        if (st) {
            av_dict_copy(&st->metadata, asf->asf_sd[i].asf_met, AV_DICT_IGNORE_SUFFIX);
            if (asf->asf_sd[i].aspect_ratio.num > 0 && asf->asf_sd[i].aspect_ratio.den > 0) {
                st->sample_aspect_ratio.num = asf->asf_sd[i].aspect_ratio.num;
                st->sample_aspect_ratio.den = asf->asf_sd[i].aspect_ratio.den;
            }
        }
    }

    return 0;

failed:
    asf_read_close(s);
    return ret;
}