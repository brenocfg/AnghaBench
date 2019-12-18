#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int size; int stream_index; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_init_packet (TYPE_1__*) ; 
 int av_packet_from_data (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int avio_close_dyn_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ff_rtp_finalize_packet(AVPacket *pkt, AVIOContext **dyn_buf, int stream_idx)
{
    int ret;
    av_init_packet(pkt);

    pkt->size         = avio_close_dyn_buf(*dyn_buf, &pkt->data);
    pkt->stream_index = stream_idx;
    *dyn_buf = NULL;
    if ((ret = av_packet_from_data(pkt, pkt->data, pkt->size)) < 0) {
        av_freep(&pkt->data);
        return ret;
    }
    return pkt->size;
}