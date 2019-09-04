#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; scalar_t__ data; } ;
typedef  TYPE_1__ AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void av_shrink_packet(AVPacket *pkt, int size)
{
    if (pkt->size <= size)
        return;
    pkt->size = size;
    memset(pkt->data + size, 0, AV_INPUT_BUFFER_PADDING_SIZE);
}