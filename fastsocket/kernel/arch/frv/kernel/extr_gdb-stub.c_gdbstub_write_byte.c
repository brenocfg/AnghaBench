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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  gdbstub_addr_map (void*) ; 
 int /*<<< orphan*/  gdbstub_addr_unmap () ; 
 int likely (int) ; 

__attribute__((used)) static inline int gdbstub_write_byte(void *addr, uint8_t val)
{
	unsigned long brr;

	if (!gdbstub_addr_map(addr))
		return 0;

	asm volatile("	movgs	gr0,brr	\n"
		     "	stb%I2	%1,%M2	\n"
		     "	movsg	brr,%0	\n"
		     : "=r"(brr)
		     : "r"(val), "m"(*(uint8_t *) addr));
	gdbstub_addr_unmap();
	return likely(!brr);
}