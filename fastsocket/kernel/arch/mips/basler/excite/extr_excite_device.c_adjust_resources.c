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
struct resource {unsigned long flags; scalar_t__ start; int /*<<< orphan*/  end; struct resource* parent; } ;

/* Variables and functions */
 unsigned long IORESOURCE_DMA ; 
 unsigned long IORESOURCE_IO ; 
 unsigned long IORESOURCE_IRQ ; 
 unsigned long IORESOURCE_MEM ; 

__attribute__((used)) static void adjust_resources(struct resource *res, unsigned int n)
{
	struct resource *p;
	const unsigned long mask = IORESOURCE_IO | IORESOURCE_MEM
				   | IORESOURCE_IRQ | IORESOURCE_DMA;

	for (p = res; p < res + n; p++) {
		const struct resource * const parent = p->parent;
		if (parent) {
			p->start += parent->start;
			p->end   += parent->start;
			p->flags =  parent->flags & mask;
		}
	}
}