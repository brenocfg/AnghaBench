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
struct uart_pmac_port {int /*<<< orphan*/ * curregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTR ; 
 size_t R5 ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  write_zsreg (struct uart_pmac_port*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zssync (struct uart_pmac_port*) ; 

__attribute__((used)) static void pmz_irda_reset(struct uart_pmac_port *uap)
{
	uap->curregs[R5] |= DTR;
	write_zsreg(uap, R5, uap->curregs[R5]);
	zssync(uap);
	mdelay(110);
	uap->curregs[R5] &= ~DTR;
	write_zsreg(uap, R5, uap->curregs[R5]);
	zssync(uap);
	mdelay(10);
}