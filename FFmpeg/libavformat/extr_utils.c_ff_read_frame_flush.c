#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int nb_streams; TYPE_1__* internal; int /*<<< orphan*/  max_probe_packets; TYPE_2__** streams; } ;
struct TYPE_7__ {scalar_t__ first_dts; int inject_global_side_data; scalar_t__ skip_samples; scalar_t__* pts_buffer; int /*<<< orphan*/  probe_packets; scalar_t__ cur_dts; scalar_t__ last_dts_for_order_check; scalar_t__ last_IP_pts; int /*<<< orphan*/ * parser; } ;
struct TYPE_6__ {scalar_t__ inject_global_side_data; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int MAX_REORDER_DELAY ; 
 scalar_t__ RELATIVE_TS_BASE ; 
 int /*<<< orphan*/  av_parser_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_packet_queue (TYPE_3__*) ; 

void ff_read_frame_flush(AVFormatContext *s)
{
    AVStream *st;
    int i, j;

    flush_packet_queue(s);

    /* Reset read state for each stream. */
    for (i = 0; i < s->nb_streams; i++) {
        st = s->streams[i];

        if (st->parser) {
            av_parser_close(st->parser);
            st->parser = NULL;
        }
        st->last_IP_pts = AV_NOPTS_VALUE;
        st->last_dts_for_order_check = AV_NOPTS_VALUE;
        if (st->first_dts == AV_NOPTS_VALUE)
            st->cur_dts = RELATIVE_TS_BASE;
        else
            /* We set the current DTS to an unspecified origin. */
            st->cur_dts = AV_NOPTS_VALUE;

        st->probe_packets = s->max_probe_packets;

        for (j = 0; j < MAX_REORDER_DELAY + 1; j++)
            st->pts_buffer[j] = AV_NOPTS_VALUE;

        if (s->internal->inject_global_side_data)
            st->inject_global_side_data = 1;

        st->skip_samples = 0;
    }
}