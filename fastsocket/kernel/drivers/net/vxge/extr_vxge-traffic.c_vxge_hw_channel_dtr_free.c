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
struct __vxge_hw_channel {size_t free_ptr; void** free_arr; } ;

/* Variables and functions */

void vxge_hw_channel_dtr_free(struct __vxge_hw_channel *channel, void *dtrh)
{
	channel->free_arr[--channel->free_ptr] = dtrh;
}