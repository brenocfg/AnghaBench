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
struct iova_domain {unsigned long dma_32bit_pfn; int /*<<< orphan*/ * cached32_node; } ;
struct iova {int /*<<< orphan*/  node; } ;

/* Variables and functions */

__attribute__((used)) static void
__cached_rbnode_insert_update(struct iova_domain *iovad,
	unsigned long limit_pfn, struct iova *new)
{
	if (limit_pfn != iovad->dma_32bit_pfn)
		return;
	iovad->cached32_node = &new->node;
}