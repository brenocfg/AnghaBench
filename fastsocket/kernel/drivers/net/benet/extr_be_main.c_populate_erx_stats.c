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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct be_rx_obj {int dummy; } ;
struct be_adapter {int dummy; } ;
struct TYPE_2__ {scalar_t__ rx_drops_no_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEx_chip (struct be_adapter*) ; 
 int /*<<< orphan*/  accumulate_16bit_val (scalar_t__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* rx_stats (struct be_rx_obj*) ; 

void populate_erx_stats(struct be_adapter *adapter,
			struct be_rx_obj *rxo,
			u32 erx_stat)
{
	if (!BEx_chip(adapter))
		rx_stats(rxo)->rx_drops_no_frags = erx_stat;
	else
		/* below erx HW counter can actually wrap around after
		 * 65535. Driver accumulates a 32-bit value
		 */
		accumulate_16bit_val(&rx_stats(rxo)->rx_drops_no_frags,
				     (u16)erx_stat);
}