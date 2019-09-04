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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_6__ {int /*<<< orphan*/  queue_len; TYPE_1__* queue; } ;
struct TYPE_5__ {scalar_t__ seq; int len; struct TYPE_5__* next; int /*<<< orphan*/ * buf; int /*<<< orphan*/  recvtime; } ;
typedef  TYPE_1__ RTPPacket ;
typedef  TYPE_2__ RTPDemuxContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_RB16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_gettime_relative () ; 
 TYPE_1__* av_mallocz (int) ; 

__attribute__((used)) static int enqueue_packet(RTPDemuxContext *s, uint8_t *buf, int len)
{
    uint16_t seq   = AV_RB16(buf + 2);
    RTPPacket **cur = &s->queue, *packet;

    /* Find the correct place in the queue to insert the packet */
    while (*cur) {
        int16_t diff = seq - (*cur)->seq;
        if (diff < 0)
            break;
        cur = &(*cur)->next;
    }

    packet = av_mallocz(sizeof(*packet));
    if (!packet)
        return AVERROR(ENOMEM);
    packet->recvtime = av_gettime_relative();
    packet->seq      = seq;
    packet->len      = len;
    packet->buf      = buf;
    packet->next     = *cur;
    *cur = packet;
    s->queue_len++;

    return 0;
}