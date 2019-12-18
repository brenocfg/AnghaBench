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

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int IOConfigReg0_1 ; 
 unsigned int IOConfigReg38_39 ; 

__attribute__((used)) static inline unsigned IOConfigReg(unsigned pfi_channel)
{
	unsigned reg = IOConfigReg0_1 + pfi_channel / 2;
	BUG_ON(reg > IOConfigReg38_39);
	return reg;
}