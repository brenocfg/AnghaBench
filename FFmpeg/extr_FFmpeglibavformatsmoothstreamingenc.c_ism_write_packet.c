#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_17__ {TYPE_4__** streams; TYPE_2__* priv_data; } ;
struct TYPE_16__ {size_t stream_index; scalar_t__ dts; int flags; } ;
struct TYPE_15__ {scalar_t__ first_dts; int /*<<< orphan*/  time_base; TYPE_1__* codecpar; } ;
struct TYPE_14__ {int /*<<< orphan*/  ctx; scalar_t__ packets_written; } ;
struct TYPE_13__ {int nb_fragments; int /*<<< orphan*/  has_video; scalar_t__ min_frag_duration; TYPE_3__* streams; } ;
struct TYPE_12__ {scalar_t__ codec_type; } ;
typedef  TYPE_2__ SmoothStreamingContext ;
typedef  TYPE_3__ OutputStream ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 scalar_t__ av_compare_ts (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ff_write_chained (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int ism_flush (TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ism_write_packet(AVFormatContext *s, AVPacket *pkt)
{
    SmoothStreamingContext *c = s->priv_data;
    AVStream *st = s->streams[pkt->stream_index];
    OutputStream *os = &c->streams[pkt->stream_index];
    int64_t end_dts = (c->nb_fragments + 1) * (int64_t) c->min_frag_duration;
    int ret;

    if (st->first_dts == AV_NOPTS_VALUE)
        st->first_dts = pkt->dts;

    if ((!c->has_video || st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) &&
        av_compare_ts(pkt->dts - st->first_dts, st->time_base,
                      end_dts, AV_TIME_BASE_Q) >= 0 &&
        pkt->flags & AV_PKT_FLAG_KEY && os->packets_written) {

        if ((ret = ism_flush(s, 0)) < 0)
            return ret;
        c->nb_fragments++;
    }

    os->packets_written++;
    return ff_write_chained(os->ctx, 0, pkt, s, 0);
}