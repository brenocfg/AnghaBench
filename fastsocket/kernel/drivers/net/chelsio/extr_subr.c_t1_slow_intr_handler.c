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
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int asic_slow_intr (int /*<<< orphan*/ *) ; 
 int fpga_slow_intr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t1_is_asic (int /*<<< orphan*/ *) ; 

int t1_slow_intr_handler(adapter_t *adapter)
{
#ifdef CONFIG_CHELSIO_T1_1G
	if (!t1_is_asic(adapter))
		return fpga_slow_intr(adapter);
#endif
	return asic_slow_intr(adapter);
}