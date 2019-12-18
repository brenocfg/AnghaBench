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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int dcplb_miss (unsigned int) ; 
 int dcplb_protection_fault (unsigned int) ; 
 int icplb_miss (unsigned int) ; 
 unsigned int raw_smp_processor_id () ; 

int cplb_hdr(int seqstat, struct pt_regs *regs)
{
	int cause = seqstat & 0x3f;
	unsigned int cpu = raw_smp_processor_id();
	switch (cause) {
	case 0x23:
		return dcplb_protection_fault(cpu);
	case 0x2C:
		return icplb_miss(cpu);
	case 0x26:
		return dcplb_miss(cpu);
	default:
		return 1;
	}
}