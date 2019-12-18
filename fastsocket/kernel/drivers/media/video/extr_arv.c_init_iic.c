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
 int /*<<< orphan*/  DEBUG (int,char*) ; 
 int /*<<< orphan*/  PLDI2CACK ; 
 int /*<<< orphan*/  PLDI2CCR ; 
 int /*<<< orphan*/  PLDI2CFREQ ; 
 int /*<<< orphan*/  PLDI2CMOD ; 
 int /*<<< orphan*/  ar_outl (int,int /*<<< orphan*/ ) ; 
 int freq ; 

void init_iic(void)
{
	DEBUG(1, "init_iic:\n");

	/*
	 * ICU Setting (iic)
	 */
	/* I2C Setting */
	ar_outl(0x0, PLDI2CCR);      	/* I2CCR Disable                   */
	ar_outl(0x0300, PLDI2CMOD); 	/* I2CMOD ACK/8b-data/7b-addr/auto */
	ar_outl(0x1, PLDI2CACK);	/* I2CACK ACK                      */

	/* I2C CLK */
	/* 50MH-100k */
	if (freq == 75) {
		ar_outl(369, PLDI2CFREQ);	/* BCLK = 75MHz */
	} else if (freq == 50) {
		ar_outl(244, PLDI2CFREQ);	/* BCLK = 50MHz */
	} else {
		ar_outl(244, PLDI2CFREQ);	/* default: BCLK = 50MHz */
	}
	ar_outl(0x1, PLDI2CCR); 	/* I2CCR Enable */
}