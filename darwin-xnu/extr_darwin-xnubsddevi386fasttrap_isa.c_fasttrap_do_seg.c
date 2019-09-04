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
typedef  int /*<<< orphan*/  x86_saved_state_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int /*<<< orphan*/  fasttrap_tracepoint_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
fasttrap_do_seg(fasttrap_tracepoint_t *tp, x86_saved_state_t *rp, user_addr_t *addr) // 64 bit
{
#pragma unused(tp, rp, addr)
	printf("fasttrap_do_seg() called while unimplemented.\n");
#if 0
	proc_t *p = curproc;
	user_desc_t *desc;
	uint16_t sel, ndx, type;
	uintptr_t limit;

	switch (tp->ftt_segment) {
	case FASTTRAP_SEG_CS:
		sel = rp->r_cs;
		break;
	case FASTTRAP_SEG_DS:
		sel = rp->r_ds;
		break;
	case FASTTRAP_SEG_ES:
		sel = rp->r_es;
		break;
	case FASTTRAP_SEG_FS:
		sel = rp->r_fs;
		break;
	case FASTTRAP_SEG_GS:
		sel = rp->r_gs;
		break;
	case FASTTRAP_SEG_SS:
		sel = rp->r_ss;
		break;
	}

	/*
	 * Make sure the given segment register specifies a user priority
	 * selector rather than a kernel selector.
	 */
	if (!SELISUPL(sel))
		return (-1);

	ndx = SELTOIDX(sel);

	/*
	 * Check the bounds and grab the descriptor out of the specified
	 * descriptor table.
	 */
	if (SELISLDT(sel)) {
		if (ndx > p->p_ldtlimit)
			return (-1);

		desc = p->p_ldt + ndx;

	} else {
		if (ndx >= NGDT)
			return (-1);

		desc = cpu_get_gdt() + ndx;
	}

	/*
	 * The descriptor must have user privilege level and it must be
	 * present in memory.
	 */
	if (desc->usd_dpl != SEL_UPL || desc->usd_p != 1)
		return (-1);

	type = desc->usd_type;

	/*
	 * If the S bit in the type field is not set, this descriptor can
	 * only be used in system context.
	 */
	if ((type & 0x10) != 0x10)
		return (-1);

	limit = USEGD_GETLIMIT(desc) * (desc->usd_gran ? PAGESIZE : 1);

	if (tp->ftt_segment == FASTTRAP_SEG_CS) {
		/*
		 * The code/data bit and readable bit must both be set.
		 */
		if ((type & 0xa) != 0xa)
			return (-1);

		if (*addr > limit)
			return (-1);
	} else {
		/*
		 * The code/data bit must be clear.
		 */
		if ((type & 0x8) != 0)
			return (-1);

		/*
		 * If the expand-down bit is clear, we just check the limit as
		 * it would naturally be applied. Otherwise, we need to check
		 * that the address is the range [limit + 1 .. 0xffff] or
		 * [limit + 1 ... 0xffffffff] depending on if the default
		 * operand size bit is set.
		 */
		if ((type & 0x4) == 0) {
			if (*addr > limit)
				return (-1);
		} else if (desc->usd_def32) {
			if (*addr < limit + 1 || 0xffff < *addr)
				return (-1);
		} else {
			if (*addr < limit + 1 || 0xffffffff < *addr)
				return (-1);
		}
	}

	*addr += USEGD_GETBASE(desc);
#endif /* 0 */
	return (0);
}