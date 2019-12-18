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
typedef  int u8 ;
struct pmac_i2c_host_kw {scalar_t__ polled; } ;

/* Variables and functions */
 int KW_I2C_IRQ_MASK ; 
 int kw_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_isr ; 

__attribute__((used)) static u8 kw_i2c_wait_interrupt(struct pmac_i2c_host_kw *host)
{
	int i, j;
	u8 isr;
	
	for (i = 0; i < 1000; i++) {
		isr = kw_read_reg(reg_isr) & KW_I2C_IRQ_MASK;
		if (isr != 0)
			return isr;

		/* This code is used with the timebase frozen, we cannot rely
		 * on udelay nor schedule when in polled mode !
		 * For now, just use a bogus loop....
		 */
		if (host->polled) {
			for (j = 1; j < 100000; j++)
				mb();
		} else
			msleep(1);
	}
	return isr;
}