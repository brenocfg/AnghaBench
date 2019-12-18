#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_13__ {int nb_streams; TYPE_1__** streams; } ;
struct TYPE_11__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  stream_index; int /*<<< orphan*/  dts; } ;
struct TYPE_12__ {TYPE_2__ sub_pkt; int /*<<< orphan*/  sub_ctx; int /*<<< orphan*/  frame_offset; } ;
struct TYPE_10__ {scalar_t__ discard; int /*<<< orphan*/  index; TYPE_3__* priv_data; int /*<<< orphan*/  time_base; } ;
typedef  TYPE_1__ AVStream ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVIStream ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVDISCARD_ALL ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 scalar_t__ INT64_MAX ; 
 scalar_t__ av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ff_read_packet (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static AVStream *get_subtitle_pkt(AVFormatContext *s, AVStream *next_st,
                                  AVPacket *pkt)
{
    AVIStream *ast, *next_ast = next_st->priv_data;
    int64_t ts, next_ts, ts_min = INT64_MAX;
    AVStream *st, *sub_st = NULL;
    int i;

    next_ts = av_rescale_q(next_ast->frame_offset, next_st->time_base,
                           AV_TIME_BASE_Q);

    for (i = 0; i < s->nb_streams; i++) {
        st  = s->streams[i];
        ast = st->priv_data;
        if (st->discard < AVDISCARD_ALL && ast && ast->sub_pkt.data) {
            ts = av_rescale_q(ast->sub_pkt.dts, st->time_base, AV_TIME_BASE_Q);
            if (ts <= next_ts && ts < ts_min) {
                ts_min = ts;
                sub_st = st;
            }
        }
    }

    if (sub_st) {
        ast               = sub_st->priv_data;
        *pkt              = ast->sub_pkt;
        pkt->stream_index = sub_st->index;

        if (ff_read_packet(ast->sub_ctx, &ast->sub_pkt) < 0)
            ast->sub_pkt.data = NULL;
    }
    return sub_st;
}