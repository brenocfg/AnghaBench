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
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ cpu_has_divec ; 
 scalar_t__ ebase ; 
 unsigned long* exception_handlers ; 
 int /*<<< orphan*/  local_flush_icache_range (scalar_t__,scalar_t__) ; 

void *set_except_vector(int n, void *addr)
{
	unsigned long handler = (unsigned long) addr;
	unsigned long old_handler = exception_handlers[n];

	exception_handlers[n] = handler;
	if (n == 0 && cpu_has_divec) {
		*(u32 *)(ebase + 0x200) = 0x08000000 |
					  (0x03ffffff & (handler >> 2));
		local_flush_icache_range(ebase + 0x200, ebase + 0x204);
	}
	return (void *)old_handler;
}