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
typedef  int u64 ;

/* Variables and functions */
 int EINVAL ; 
 int IBSCTL_LVT_OFFSET_MASK ; 
 int IBSCTL_LVT_OFFSET_VALID ; 
 int /*<<< orphan*/  MSR_AMD64_IBSCTL ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int get_ibs_offset(void)
{
	u64 val;

	rdmsrl(MSR_AMD64_IBSCTL, val);
	if (!(val & IBSCTL_LVT_OFFSET_VALID))
		return -EINVAL;

	return val & IBSCTL_LVT_OFFSET_MASK;
}