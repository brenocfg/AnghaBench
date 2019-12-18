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
struct smm_regs {int eax; int edx; } ;

/* Variables and functions */
 int i8k_smm (struct smm_regs*) ; 

__attribute__((used)) static int i8k_get_dell_signature(int req_fn)
{
	struct smm_regs regs = { .eax = req_fn, };
	int rc;

	if ((rc = i8k_smm(&regs)) < 0)
		return rc;

	return regs.eax == 1145651527 && regs.edx == 1145392204 ? 0 : -1;
}