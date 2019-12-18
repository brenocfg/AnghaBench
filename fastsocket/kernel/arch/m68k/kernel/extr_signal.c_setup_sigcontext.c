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
struct sigcontext {unsigned long sc_mask; int sc_formatvec; int /*<<< orphan*/  sc_pc; int /*<<< orphan*/  sc_sr; int /*<<< orphan*/  sc_a1; int /*<<< orphan*/  sc_a0; int /*<<< orphan*/  sc_d1; int /*<<< orphan*/  sc_d0; int /*<<< orphan*/  sc_usp; } ;
struct pt_regs {int format; int vector; int /*<<< orphan*/  pc; int /*<<< orphan*/  sr; int /*<<< orphan*/  a1; int /*<<< orphan*/  a0; int /*<<< orphan*/  d1; int /*<<< orphan*/  d0; } ;

/* Variables and functions */
 int /*<<< orphan*/  rdusp () ; 
 int /*<<< orphan*/  save_fpu_state (struct sigcontext*,struct pt_regs*) ; 

__attribute__((used)) static void setup_sigcontext(struct sigcontext *sc, struct pt_regs *regs,
			     unsigned long mask)
{
	sc->sc_mask = mask;
	sc->sc_usp = rdusp();
	sc->sc_d0 = regs->d0;
	sc->sc_d1 = regs->d1;
	sc->sc_a0 = regs->a0;
	sc->sc_a1 = regs->a1;
	sc->sc_sr = regs->sr;
	sc->sc_pc = regs->pc;
	sc->sc_formatvec = regs->format << 12 | regs->vector;
	save_fpu_state(sc, regs);
}