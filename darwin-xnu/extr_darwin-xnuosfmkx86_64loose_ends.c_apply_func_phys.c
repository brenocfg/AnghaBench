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
typedef  int vm_size_t ;
typedef  int uint32_t ;
typedef  scalar_t__ addr64_t ;

/* Variables and functions */
 int NBPG ; 
 void* PHYSMAP_PTOV (scalar_t__) ; 
 int /*<<< orphan*/  panic (char*) ; 

int
apply_func_phys(
		addr64_t dst64,
		vm_size_t bytes,
		int (*func)(void * buffer, vm_size_t bytes, void * arg),
		void * arg)
{
	/* Not necessary for K64 - but ensure we stay within a page */
	if (((((uint32_t)dst64 & (NBPG-1)) + bytes) > NBPG) ) {
	        panic("apply_func_phys alignment");
	}

	return func(PHYSMAP_PTOV(dst64), bytes, arg);
}