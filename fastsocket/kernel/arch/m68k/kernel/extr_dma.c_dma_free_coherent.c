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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (void*) ; 

void dma_free_coherent(struct device *dev, size_t size,
		       void *addr, dma_addr_t handle)
{
	pr_debug("dma_free_coherent: %p, %x\n", addr, handle);
	vfree(addr);
}