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
 scalar_t__ dma_release_from_coherent (struct device*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int /*<<< orphan*/  kfree (void*) ; 

void dma_free_coherent(struct device *dev, size_t size, void *cpu_addr, dma_addr_t handle)
{
	if (dma_release_from_coherent(dev, get_order(size), cpu_addr))
		return;
	kfree(cpu_addr);
}