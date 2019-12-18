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
 int /*<<< orphan*/  DCRN_SDR0_UART0 ; 
 int /*<<< orphan*/  DCRN_SDR0_UART1 ; 
 int /*<<< orphan*/  DCRN_SDR0_UART2 ; 
 int /*<<< orphan*/  DCRN_SDR0_UART3 ; 
 unsigned int SDR0_READ (int /*<<< orphan*/ ) ; 
 unsigned int __fix_zero (unsigned int,int) ; 
 int /*<<< orphan*/  dt_fixup_clock (char const*,unsigned int) ; 

__attribute__((used)) static void eplike_fixup_uart_clk(int index, const char *path,
				  unsigned int ser_clk,
				  unsigned int plb_clk)
{
	unsigned int sdr;
	unsigned int clock;

	switch (index) {
	case 0:
		sdr = SDR0_READ(DCRN_SDR0_UART0);
		break;
	case 1:
		sdr = SDR0_READ(DCRN_SDR0_UART1);
		break;
	case 2:
		sdr = SDR0_READ(DCRN_SDR0_UART2);
		break;
	case 3:
		sdr = SDR0_READ(DCRN_SDR0_UART3);
		break;
	default:
		return;
	}

	if (sdr & 0x00800000u)
		clock = ser_clk;
	else
		clock = plb_clk / __fix_zero(sdr & 0xff, 256);

	dt_fixup_clock(path, clock);
}