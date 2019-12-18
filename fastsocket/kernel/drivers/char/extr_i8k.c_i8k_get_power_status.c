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
struct smm_regs {int eax; } ;

/* Variables and functions */
 int I8K_AC ; 
 int I8K_BATTERY ; 
 int I8K_POWER_AC ; 
 int I8K_SMM_POWER_STATUS ; 
 int i8k_smm (struct smm_regs*) ; 

__attribute__((used)) static int i8k_get_power_status(void)
{
	struct smm_regs regs = { .eax = I8K_SMM_POWER_STATUS, };
	int rc;

	if ((rc = i8k_smm(&regs)) < 0)
		return rc;

	return (regs.eax & 0xff) == I8K_POWER_AC ? I8K_AC : I8K_BATTERY;
}