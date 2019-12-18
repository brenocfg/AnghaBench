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
struct z8530_channel {int dummy; } ;

/* Variables and functions */
 int END_FR ; 
 int /*<<< orphan*/  ERR_RES ; 
 int /*<<< orphan*/  R1 ; 
 int /*<<< orphan*/  RES_H_IUS ; 
 int /*<<< orphan*/  RES_Rx_CRC ; 
 int /*<<< orphan*/  read_zsdata (struct z8530_channel*) ; 
 int read_zsreg (struct z8530_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_zsctrl (struct z8530_channel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void z8530_rx_clear(struct z8530_channel *c)
{
	/*
	 *	Data and status bytes
	 */
	u8 stat;

	read_zsdata(c);
	stat=read_zsreg(c, R1);
	
	if(stat&END_FR)
		write_zsctrl(c, RES_Rx_CRC);
	/*
	 *	Clear irq
	 */
	write_zsctrl(c, ERR_RES);
	write_zsctrl(c, RES_H_IUS);
}