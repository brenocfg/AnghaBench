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
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int GFP_KERNEL ; 
 int __GFP_NOFAIL ; 
 scalar_t__ __get_free_page (int) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  install_p2mtop_page (unsigned long,unsigned long*) ; 

__attribute__((used)) static void alloc_p2m(unsigned long pfn)
{
	unsigned long *p;

	p = (void *)__get_free_page(GFP_KERNEL | __GFP_NOFAIL);
	BUG_ON(p == NULL);

	if (!install_p2mtop_page(pfn, p))
		free_page((unsigned long)p);
}