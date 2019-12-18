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
struct smm_regs {int eax; int ebx; } ;

/* Variables and functions */
 int I8K_MAX_TEMP ; 
 int I8K_SMM_GET_TEMP ; 
 int i8k_smm (struct smm_regs*) ; 

__attribute__((used)) static int i8k_get_temp(int sensor)
{
	struct smm_regs regs = { .eax = I8K_SMM_GET_TEMP, };
	int rc;
	int temp;

#ifdef I8K_TEMPERATURE_BUG
	static int prev;
#endif
	regs.ebx = sensor & 0xff;
	if ((rc = i8k_smm(&regs)) < 0)
		return rc;

	temp = regs.eax & 0xff;

#ifdef I8K_TEMPERATURE_BUG
	/*
	 * Sometimes the temperature sensor returns 0x99, which is out of range.
	 * In this case we return (once) the previous cached value. For example:
	 # 1003655137 00000058 00005a4b
	 # 1003655138 00000099 00003a80 <--- 0x99 = 153 degrees
	 # 1003655139 00000054 00005c52
	 */
	if (temp > I8K_MAX_TEMP) {
		temp = prev;
		prev = I8K_MAX_TEMP;
	} else {
		prev = temp;
	}
#endif

	return temp;
}