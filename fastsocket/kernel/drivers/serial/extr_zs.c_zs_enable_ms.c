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
struct zs_scc {int /*<<< orphan*/  zlock; struct zs_port* zport; } ;
struct zs_port {int* regs; struct zs_scc* scc; } ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int CTSIE ; 
 int DCDIE ; 
 int EXT_INT_ENAB ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R1 ; 
 int /*<<< orphan*/  R15 ; 
 int RES_EXT_INT ; 
 int SYNCIE ; 
 size_t ZS_CHAN_A ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct zs_port* to_zport (struct uart_port*) ; 
 int /*<<< orphan*/  write_zsreg (struct zs_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zs_raw_xor_mctrl (struct zs_port*) ; 

__attribute__((used)) static void zs_enable_ms(struct uart_port *uport)
{
	struct zs_port *zport = to_zport(uport);
	struct zs_scc *scc = zport->scc;
	struct zs_port *zport_a = &scc->zport[ZS_CHAN_A];

	if (zport == zport_a)
		return;

	spin_lock(&scc->zlock);

	/* Clear Ext interrupts if not being handled already.  */
	if (!(zport_a->regs[1] & EXT_INT_ENAB))
		write_zsreg(zport_a, R0, RES_EXT_INT);

	/* A-side DCD tracks RI and SYNC tracks DSR.  */
	zport_a->regs[1] |= EXT_INT_ENAB;
	zport_a->regs[15] |= DCDIE | SYNCIE;

	/* This-side DCD tracks DCD and CTS tracks CTS.  */
	zport->regs[15] |= DCDIE | CTSIE;

	zs_raw_xor_mctrl(zport);

	write_zsreg(zport_a, R1, zport_a->regs[1]);
	write_zsreg(zport_a, R15, zport_a->regs[15]);
	write_zsreg(zport, R15, zport->regs[15]);
	spin_unlock(&scc->zlock);
}