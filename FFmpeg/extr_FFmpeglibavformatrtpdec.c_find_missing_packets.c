#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_5__ {scalar_t__ seq; TYPE_1__* queue; } ;
struct TYPE_4__ {scalar_t__ seq; struct TYPE_4__* next; } ;
typedef  TYPE_1__ RTPPacket ;
typedef  TYPE_2__ RTPDemuxContext ;

/* Variables and functions */

__attribute__((used)) static int find_missing_packets(RTPDemuxContext *s, uint16_t *first_missing,
                                uint16_t *missing_mask)
{
    int i;
    uint16_t next_seq = s->seq + 1;
    RTPPacket *pkt = s->queue;

    if (!pkt || pkt->seq == next_seq)
        return 0;

    *missing_mask = 0;
    for (i = 1; i <= 16; i++) {
        uint16_t missing_seq = next_seq + i;
        while (pkt) {
            int16_t diff = pkt->seq - missing_seq;
            if (diff >= 0)
                break;
            pkt = pkt->next;
        }
        if (!pkt)
            break;
        if (pkt->seq == missing_seq)
            continue;
        *missing_mask |= 1 << (i - 1);
    }

    *first_missing = next_seq;
    return 1;
}