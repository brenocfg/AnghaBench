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
 scalar_t__ L1_CODE_LENGTH ; 
 scalar_t__ L1_CODE_START ; 
 int /*<<< orphan*/  pr_err (char*,void const*,size_t) ; 
 int /*<<< orphan*/  show_stack (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool isram_check_addr(const void *addr, size_t n)
{
	if ((addr >= (void *)L1_CODE_START) &&
	    (addr < (void *)(L1_CODE_START + L1_CODE_LENGTH))) {
		if ((addr + n) > (void *)(L1_CODE_START + L1_CODE_LENGTH)) {
			show_stack(NULL, NULL);
			pr_err("copy involving %p length (%zu) too long\n", addr, n);
		}
		return true;
	}
	return false;
}