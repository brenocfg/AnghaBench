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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  gdbstub_addr_map (void const*) ; 
 int /*<<< orphan*/  gdbstub_addr_unmap () ; 
 int likely (int) ; 

__attribute__((used)) static inline int gdbstub_read_dword(const void *addr, uint32_t *_res)
{
	unsigned long brr;
	uint32_t res;

	if (!gdbstub_addr_map(addr))
		return 0;

	asm volatile("	movgs	gr0,brr	\n"
		     "	ld%I2	%M2,%0	\n"
		     "	movsg	brr,%1	\n"
		     : "=r"(res), "=r"(brr)
		     : "m"(*(uint32_t *) addr));
	*_res = res;
	gdbstub_addr_unmap();
	return likely(!brr);
}