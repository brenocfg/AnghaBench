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
struct iova_domain {unsigned long dma_32bit_pfn; int /*<<< orphan*/ * cached32_node; int /*<<< orphan*/  rbroot; int /*<<< orphan*/  iova_rbtree_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void
init_iova_domain(struct iova_domain *iovad, unsigned long pfn_32bit)
{
	spin_lock_init(&iovad->iova_rbtree_lock);
	iovad->rbroot = RB_ROOT;
	iovad->cached32_node = NULL;
	iovad->dma_32bit_pfn = pfn_32bit;
}