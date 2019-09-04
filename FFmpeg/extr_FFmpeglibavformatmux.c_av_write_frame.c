#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_3__** streams; TYPE_2__* pb; TYPE_1__* oformat; } ;
struct TYPE_19__ {size_t stream_index; } ;
struct TYPE_18__ {int /*<<< orphan*/  nb_frames; } ;
struct TYPE_17__ {int error; } ;
struct TYPE_16__ {int flags; int (* write_packet ) (TYPE_5__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVFMT_ALLOW_FLUSH ; 
 int do_packet_auto_bsf (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  flush_if_needed (TYPE_5__*) ; 
 int prepare_input_packet (TYPE_5__*,TYPE_4__*) ; 
 int stub1 (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int write_packet (TYPE_5__*,TYPE_4__*) ; 

int av_write_frame(AVFormatContext *s, AVPacket *pkt)
{
    int ret;

    ret = prepare_input_packet(s, pkt);
    if (ret < 0)
        return ret;

    if (!pkt) {
        if (s->oformat->flags & AVFMT_ALLOW_FLUSH) {
            ret = s->oformat->write_packet(s, NULL);
            flush_if_needed(s);
            if (ret >= 0 && s->pb && s->pb->error < 0)
                ret = s->pb->error;
            return ret;
        }
        return 1;
    }

    ret = do_packet_auto_bsf(s, pkt);
    if (ret <= 0)
        return ret;

#if FF_API_COMPUTE_PKT_FIELDS2 && FF_API_LAVF_AVCTX
    ret = compute_muxer_pkt_fields(s, s->streams[pkt->stream_index], pkt);

    if (ret < 0 && !(s->oformat->flags & AVFMT_NOTIMESTAMPS))
        return ret;
#endif

    ret = write_packet(s, pkt);
    if (ret >= 0 && s->pb && s->pb->error < 0)
        ret = s->pb->error;

    if (ret >= 0)
        s->streams[pkt->stream_index]->nb_frames++;
    return ret;
}