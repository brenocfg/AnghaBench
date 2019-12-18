#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct pt_regs {int dummy; } ;
struct op_msrs {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  counter_address; int /*<<< orphan*/  cccr_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_LVTPC ; 
 int APIC_LVT_MASKED ; 
 int /*<<< orphan*/  CCCR_CLEAR_OVF (unsigned long) ; 
 scalar_t__ CCCR_OVF_P (unsigned long) ; 
 unsigned long OP_CTR_OVERFLOW ; 
 unsigned long VIRT_CTR (unsigned long,int) ; 
 int apic_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apic_write (int /*<<< orphan*/ ,int) ; 
 unsigned long get_stagger () ; 
 int num_counters ; 
 int /*<<< orphan*/  oprofile_add_sample (struct pt_regs* const,int) ; 
 TYPE_1__* p4_counters ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 scalar_t__* reset_value ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int p4_check_ctrs(struct pt_regs * const regs,
			 struct op_msrs const * const msrs)
{
	unsigned long ctr, low, high, stag, real;
	int i;

	stag = get_stagger();

	for (i = 0; i < num_counters; ++i) {

		if (!reset_value[i])
			continue;

		/*
		 * there is some eccentricity in the hardware which
		 * requires that we perform 2 extra corrections:
		 *
		 * - check both the CCCR:OVF flag for overflow and the
		 *   counter high bit for un-flagged overflows.
		 *
		 * - write the counter back twice to ensure it gets
		 *   updated properly.
		 *
		 * the former seems to be related to extra NMIs happening
		 * during the current NMI; the latter is reported as errata
		 * N15 in intel doc 249199-029, pentium 4 specification
		 * update, though their suggested work-around does not
		 * appear to solve the problem.
		 */

		real = VIRT_CTR(stag, i);

		rdmsr(p4_counters[real].cccr_address, low, high);
		rdmsr(p4_counters[real].counter_address, ctr, high);
		if (CCCR_OVF_P(low) || !(ctr & OP_CTR_OVERFLOW)) {
			oprofile_add_sample(regs, i);
			wrmsrl(p4_counters[real].counter_address,
			       -(u64)reset_value[i]);
			CCCR_CLEAR_OVF(low);
			wrmsr(p4_counters[real].cccr_address, low, high);
			wrmsrl(p4_counters[real].counter_address,
			       -(u64)reset_value[i]);
		}
	}

	/* P4 quirk: you have to re-unmask the apic vector */
	apic_write(APIC_LVTPC, apic_read(APIC_LVTPC) & ~APIC_LVT_MASKED);

	/* See op_model_ppro.c */
	return 1;
}