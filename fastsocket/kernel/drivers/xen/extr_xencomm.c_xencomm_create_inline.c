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
struct xencomm_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (unsigned long) ; 
 unsigned long XENCOMM_INLINE_FLAG ; 
 int /*<<< orphan*/  xencomm_is_phys_contiguous (unsigned long) ; 
 scalar_t__ xencomm_pa (void*) ; 

__attribute__((used)) static struct xencomm_handle *xencomm_create_inline(void *ptr)
{
	unsigned long paddr;

	BUG_ON(!xencomm_is_phys_contiguous((unsigned long)ptr));

	paddr = (unsigned long)xencomm_pa(ptr);
	BUG_ON(paddr & XENCOMM_INLINE_FLAG);
	return (struct xencomm_handle *)(paddr | XENCOMM_INLINE_FLAG);
}