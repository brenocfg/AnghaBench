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

/* Variables and functions */
 unsigned short HZ ; 
 int TCTR_MODE_2 ; 
 int TCTR_RL_RW_LH8 ; 
 int TCTR_SC_CTR0 ; 
 unsigned short __res_bus_clock_speed_HZ ; 
 int /*<<< orphan*/  __set_TCSR_DATA (int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  __set_TCTR (int) ; 
 int /*<<< orphan*/  __set_TPRV (unsigned short) ; 
 int /*<<< orphan*/  __set_TxCKSL_DATA (int /*<<< orphan*/ ,unsigned short) ; 

void time_divisor_init(void)
{
	unsigned short base, pre, prediv;

	/* set the scheduling timer going */
	pre = 1;
	prediv = 4;
	base = __res_bus_clock_speed_HZ / pre / HZ / (1 << prediv);

	__set_TPRV(pre);
	__set_TxCKSL_DATA(0, prediv);
	__set_TCTR(TCTR_SC_CTR0 | TCTR_RL_RW_LH8 | TCTR_MODE_2);
	__set_TCSR_DATA(0, base & 0xff);
	__set_TCSR_DATA(0, base >> 8);
}