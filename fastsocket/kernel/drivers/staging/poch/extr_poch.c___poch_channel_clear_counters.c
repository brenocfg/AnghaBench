#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ fifo_overflow; scalar_t__ fifo_empty; scalar_t__ pll_unlock; } ;
struct channel_info {TYPE_1__ counters; } ;

/* Variables and functions */

__attribute__((used)) static void __poch_channel_clear_counters(struct channel_info *channel)
{
	channel->counters.pll_unlock = 0;
	channel->counters.fifo_empty = 0;
	channel->counters.fifo_overflow = 0;
}