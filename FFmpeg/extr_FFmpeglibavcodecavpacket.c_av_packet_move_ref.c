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
struct TYPE_5__ {scalar_t__ size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  av_init_packet (TYPE_1__*) ; 

void av_packet_move_ref(AVPacket *dst, AVPacket *src)
{
    *dst = *src;
    av_init_packet(src);
    src->data = NULL;
    src->size = 0;
}