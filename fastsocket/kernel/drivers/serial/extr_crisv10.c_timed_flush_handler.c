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
struct e100_serial {scalar_t__ uses_dma_in; } ;

/* Variables and functions */
 scalar_t__ CONFIG_ETRAX_SERIAL_RX_TIMEOUT_TICKS ; 
 int NR_PORTS ; 
 int /*<<< orphan*/  check_flush_timeout (struct e100_serial*) ; 
 int /*<<< orphan*/  flush_timer ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct e100_serial* rs_table ; 

__attribute__((used)) static void
timed_flush_handler(unsigned long ptr)
{
	struct e100_serial *info;
	int i;

#ifdef CONFIG_SVINTO_SIM
	return;
#endif

	for (i = 0; i < NR_PORTS; i++) {
		info = rs_table + i;
		if (info->uses_dma_in)
			check_flush_timeout(info);
	}

	/* restart flush timer */
	mod_timer(&flush_timer, jiffies + CONFIG_ETRAX_SERIAL_RX_TIMEOUT_TICKS);
}