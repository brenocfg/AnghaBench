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
 int /*<<< orphan*/  MSR_IA32_MCx_STATUS (int) ; 
 int banks ; 
 int /*<<< orphan*/  mce_wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int,unsigned long*) ; 

__attribute__((used)) static void mce_clear_state(unsigned long *toclear)
{
	int i;

	for (i = 0; i < banks; i++) {
		if (test_bit(i, toclear))
			mce_wrmsrl(MSR_IA32_MCx_STATUS(i), 0);
	}
}