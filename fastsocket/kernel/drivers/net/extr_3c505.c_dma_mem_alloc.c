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
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long __get_dma_pages (int /*<<< orphan*/ ,int) ; 
 int get_order (int) ; 

__attribute__((used)) static unsigned long dma_mem_alloc(int size)
{
	int order = get_order(size);
	return __get_dma_pages(GFP_KERNEL, order);
}