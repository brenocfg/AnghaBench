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
typedef  unsigned long vm_offset_t ;

/* Variables and functions */
 int log2 (unsigned long) ; 

__attribute__((used)) static inline vm_offset_t
roundup_pow2(vm_offset_t size)
{
	return 1UL << (log2(size - 1) + 1);
}