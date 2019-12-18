#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long addrlo; } ;
typedef  TYPE_1__ rraddr ;
typedef  unsigned long dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static inline void set_rraddr(rraddr *ra, dma_addr_t addr)
{
	unsigned long baddr = addr;
#if (BITS_PER_LONG == 64)
	ra->addrlo = baddr;
#else
    /* Don't bother setting zero every time */
	ra->addrlo = baddr;
#endif
	mb();
}