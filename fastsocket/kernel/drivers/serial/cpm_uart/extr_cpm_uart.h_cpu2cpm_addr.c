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
typedef  scalar_t__ u32 ;
struct uart_cpm_port {scalar_t__ mem_size; unsigned long dma_addr; int /*<<< orphan*/  mem_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static inline unsigned long cpu2cpm_addr(void *addr,
                                         struct uart_cpm_port *pinfo)
{
	int offset;
	u32 val = (u32)addr;
	u32 mem = (u32)pinfo->mem_addr;
	/* sane check */
	if (likely(val >= mem && val < mem + pinfo->mem_size)) {
		offset = val - mem;
		return pinfo->dma_addr + offset;
	}
	/* something nasty happened */
	BUG();
	return 0;
}