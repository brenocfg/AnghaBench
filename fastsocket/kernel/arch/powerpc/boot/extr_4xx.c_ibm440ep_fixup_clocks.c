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
 unsigned int __ibm440eplike_fixup_clocks (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eplike_fixup_uart_clk (int,char*,unsigned int,unsigned int) ; 

void ibm440ep_fixup_clocks(unsigned int sys_clk,
			   unsigned int ser_clk,
			   unsigned int tmr_clk)
{
	unsigned int plb_clk = __ibm440eplike_fixup_clocks(sys_clk, tmr_clk, 0);

	/* serial clocks beed fixup based on int/ext */
	eplike_fixup_uart_clk(0, "/plb/opb/serial@ef600300", ser_clk, plb_clk);
	eplike_fixup_uart_clk(1, "/plb/opb/serial@ef600400", ser_clk, plb_clk);
	eplike_fixup_uart_clk(2, "/plb/opb/serial@ef600500", ser_clk, plb_clk);
	eplike_fixup_uart_clk(3, "/plb/opb/serial@ef600600", ser_clk, plb_clk);
}