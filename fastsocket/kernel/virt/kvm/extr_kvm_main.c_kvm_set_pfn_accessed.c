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
typedef  int /*<<< orphan*/  pfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_is_mmio_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_page_accessed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_to_page (int /*<<< orphan*/ ) ; 

void kvm_set_pfn_accessed(pfn_t pfn)
{
	if (!kvm_is_mmio_pfn(pfn))
		mark_page_accessed(pfn_to_page(pfn));
}