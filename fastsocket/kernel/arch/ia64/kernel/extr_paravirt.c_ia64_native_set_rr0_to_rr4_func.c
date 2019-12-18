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
 int /*<<< orphan*/  ia64_native_set_rr0_to_rr4 (unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static void
ia64_native_set_rr0_to_rr4_func(unsigned long val0, unsigned long val1,
				unsigned long val2, unsigned long val3,
				unsigned long val4)
{
	ia64_native_set_rr0_to_rr4(val0, val1, val2, val3, val4);
}