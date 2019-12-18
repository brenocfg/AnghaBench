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
 unsigned long __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  high_memory ; 

__attribute__((used)) static inline int valid_phys_addr_range(unsigned long addr, size_t count)
{
	if (addr + count > __pa(high_memory))
		return 0;

	return 1;
}