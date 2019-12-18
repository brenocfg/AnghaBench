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
 scalar_t__ in_mem (unsigned long,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static inline
int in_mem_const_off(unsigned long addr, unsigned long size, unsigned long off,
                     unsigned long const_addr, unsigned long const_size)
{
	return const_size &&
	       in_mem(addr, size, const_addr + off, const_addr + const_size);
}