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
struct switch_stack {unsigned long ar_bspstore; unsigned long ar_rnat; } ;
struct pt_regs {int cr_ifs; scalar_t__ ar_bspstore; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,void*,...) ; 
 int IA64_RBS_OFFSET ; 
 scalar_t__ current ; 
 int /*<<< orphan*/  ia64_peek (scalar_t__,struct switch_stack*,unsigned long,unsigned long,unsigned long*) ; 
 unsigned long ia64_rse_num_regs (unsigned long*,unsigned long*) ; 
 unsigned long* ia64_rse_rnat_addr (unsigned long*) ; 
 unsigned long* ia64_rse_skip_regs (unsigned long*,long) ; 
 unsigned long ia64_rse_slot_num (unsigned long*) ; 
 long rotate_reg (long,long,long) ; 
 int /*<<< orphan*/  user_stack (scalar_t__,struct pt_regs*) ; 

__attribute__((used)) static void
get_rse_reg (struct pt_regs *regs, unsigned long r1, unsigned long *val, int *nat)
{
	struct switch_stack *sw = (struct switch_stack *) regs - 1;
	unsigned long *bsp, *addr, *rnat_addr, *ubs_end, *bspstore;
	unsigned long *kbs = (void *) current + IA64_RBS_OFFSET;
	unsigned long rnats, nat_mask;
	unsigned long on_kbs;
	long sof = (regs->cr_ifs) & 0x7f;
	long sor = 8 * ((regs->cr_ifs >> 14) & 0xf);
	long rrb_gr = (regs->cr_ifs >> 18) & 0x7f;
	long ridx = r1 - 32;

	if (ridx >= sof) {
		/* read of out-of-frame register returns an undefined value; 0 in our case.  */
		DPRINT("ignoring read from r%lu; only %lu registers are allocated!\n", r1, sof);
		goto fail;
	}

	if (ridx < sor)
		ridx = rotate_reg(sor, rrb_gr, ridx);

	DPRINT("r%lu, sw.bspstore=%lx pt.bspstore=%lx sof=%ld sol=%ld ridx=%ld\n",
	       r1, sw->ar_bspstore, regs->ar_bspstore, sof, (regs->cr_ifs >> 7) & 0x7f, ridx);

	on_kbs = ia64_rse_num_regs(kbs, (unsigned long *) sw->ar_bspstore);
	addr = ia64_rse_skip_regs((unsigned long *) sw->ar_bspstore, -sof + ridx);
	if (addr >= kbs) {
		/* the register is on the kernel backing store: easy... */
		*val = *addr;
		if (nat) {
			rnat_addr = ia64_rse_rnat_addr(addr);
			if ((unsigned long) rnat_addr >= sw->ar_bspstore)
				rnat_addr = &sw->ar_rnat;
			nat_mask = 1UL << ia64_rse_slot_num(addr);
			*nat = (*rnat_addr & nat_mask) != 0;
		}
		return;
	}

	if (!user_stack(current, regs)) {
		DPRINT("ignoring kernel read of r%lu; register isn't on the RBS!", r1);
		goto fail;
	}

	bspstore = (unsigned long *)regs->ar_bspstore;
	ubs_end = ia64_rse_skip_regs(bspstore, on_kbs);
	bsp     = ia64_rse_skip_regs(ubs_end, -sof);
	addr    = ia64_rse_skip_regs(bsp, ridx);

	DPRINT("ubs_end=%p bsp=%p addr=%p\n", (void *) ubs_end, (void *) bsp, (void *) addr);

	ia64_peek(current, sw, (unsigned long) ubs_end, (unsigned long) addr, val);

	if (nat) {
		rnat_addr = ia64_rse_rnat_addr(addr);
		nat_mask = 1UL << ia64_rse_slot_num(addr);

		DPRINT("rnat @%p = 0x%lx\n", (void *) rnat_addr, rnats);

		ia64_peek(current, sw, (unsigned long) ubs_end, (unsigned long) rnat_addr, &rnats);
		*nat = (rnats & nat_mask) != 0;
	}
	return;

  fail:
	*val = 0;
	if (nat)
		*nat = 0;
	return;
}