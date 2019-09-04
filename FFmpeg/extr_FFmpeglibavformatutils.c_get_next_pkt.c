#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* internal; } ;
struct TYPE_8__ {struct TYPE_8__* next; } ;
struct TYPE_7__ {TYPE_2__* parse_queue; TYPE_2__* packet_buffer_end; } ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  TYPE_2__ AVPacketList ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */

__attribute__((used)) static AVPacketList *get_next_pkt(AVFormatContext *s, AVStream *st, AVPacketList *pktl)
{
    if (pktl->next)
        return pktl->next;
    if (pktl == s->internal->packet_buffer_end)
        return s->internal->parse_queue;
    return NULL;
}