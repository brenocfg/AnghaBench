#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ prev_ret; scalar_t__ queue_len; scalar_t__ seq; TYPE_1__* queue; } ;
struct TYPE_5__ {struct TYPE_5__* buf; struct TYPE_5__* next; } ;
typedef  TYPE_1__ RTPPacket ;
typedef  TYPE_2__ RTPDemuxContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 

void ff_rtp_reset_packet_queue(RTPDemuxContext *s)
{
    while (s->queue) {
        RTPPacket *next = s->queue->next;
        av_freep(&s->queue->buf);
        av_freep(&s->queue);
        s->queue = next;
    }
    s->seq       = 0;
    s->queue_len = 0;
    s->prev_ret  = 0;
}