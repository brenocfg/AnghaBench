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
typedef  int uint ;
typedef  int u32 ;
struct uart_port {int dummy; } ;
struct mpsc_port_info {int MPSC_CHR_10_m; scalar_t__ mpsc_base; scalar_t__ mirror_regs; } ;

/* Variables and functions */
 scalar_t__ MPSC_CHR_10 ; 
 int TIOCM_CAR ; 
 int TIOCM_CTS ; 
 int TIOCM_DSR ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static uint mpsc_get_mctrl(struct uart_port *port)
{
	struct mpsc_port_info *pi = (struct mpsc_port_info *)port;
	u32 mflags, status;

	status = (pi->mirror_regs) ? pi->MPSC_CHR_10_m
		: readl(pi->mpsc_base + MPSC_CHR_10);

	mflags = 0;
	if (status & 0x1)
		mflags |= TIOCM_CTS;
	if (status & 0x2)
		mflags |= TIOCM_CAR;

	return mflags | TIOCM_DSR;	/* No way to tell if DSR asserted */
}