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
 int CPLB_UNKNOWN_ERR ; 
#define  VEC_CPLB_I_M 129 
#define  VEC_CPLB_M 128 
 int dcplb_miss (unsigned int) ; 
 int icplb_miss (unsigned int) ; 
 unsigned int raw_smp_processor_id () ; 

int cplb_hdr(int seqstat, struct pt_regs *regs)
{
	int cause = seqstat & 0x3f;
	unsigned int cpu = raw_smp_processor_id();
	switch (cause) {
	case VEC_CPLB_I_M:
		return icplb_miss(cpu);
	case VEC_CPLB_M:
		return dcplb_miss(cpu);
	default:
		return CPLB_UNKNOWN_ERR;
	}
}