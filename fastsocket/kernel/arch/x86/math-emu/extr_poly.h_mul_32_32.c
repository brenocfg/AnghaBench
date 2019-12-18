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

__attribute__((used)) static inline unsigned long mul_32_32(const unsigned long arg1,
				      const unsigned long arg2)
{
	int retval;
	asm volatile ("mull %2; movl %%edx,%%eax":"=a" (retval)
		      :"0"(arg1), "g"(arg2)
		      :"dx");
	return retval;
}