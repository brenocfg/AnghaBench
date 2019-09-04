#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/  pkt; } ;
typedef  TYPE_1__ AVPacketList ;
typedef  int /*<<< orphan*/  AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (TYPE_1__*) ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 

int ff_packet_list_get(AVPacketList **pkt_buffer,
                       AVPacketList **pkt_buffer_end,
                       AVPacket      *pkt)
{
    AVPacketList *pktl;
    av_assert0(*pkt_buffer);
    pktl        = *pkt_buffer;
    *pkt        = pktl->pkt;
    *pkt_buffer = pktl->next;
    if (!pktl->next)
        *pkt_buffer_end = NULL;
    av_freep(&pktl);
    return 0;
}