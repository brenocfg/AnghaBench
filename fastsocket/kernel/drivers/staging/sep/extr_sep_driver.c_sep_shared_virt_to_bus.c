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
struct sep_device {int shared_bus; void* shared_addr; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  edbg (char*,int,void*) ; 

__attribute__((used)) static dma_addr_t sep_shared_virt_to_bus(struct sep_device *sep,
						void *virt_address)
{
	dma_addr_t pa = sep->shared_bus + (virt_address - sep->shared_addr);
	edbg("sep: virt to bus b %08llx v %p\n", pa, virt_address);
	return pa;
}