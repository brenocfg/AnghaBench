#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct frame {unsigned int len; scalar_t__* data; } ;

/* Variables and functions */

__attribute__((used)) static void carlu_loopback_mark_tx_frames(struct frame *frame)
{
	unsigned int i;

	for (i = 0; i < frame->len; i++)
		frame->data[i] = (uint8_t) i;
}