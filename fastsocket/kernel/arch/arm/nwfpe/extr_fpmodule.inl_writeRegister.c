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
struct pt_regs {unsigned long* uregs; } ;

/* Variables and functions */
 struct pt_regs* GET_USERREG () ; 

__attribute__((used)) static inline void
writeRegister(const unsigned int nReg, const unsigned long val)
{
	struct pt_regs *regs = GET_USERREG();
	regs->uregs[nReg] = val;
}