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
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int PAGE_SHIFT ; 
 int SRMMU_PTD_PMASK ; 
 struct page* pfn_to_page (int) ; 
 int pmd_val (int /*<<< orphan*/ ) ; 
 scalar_t__ srmmu_device_memory (int) ; 

__attribute__((used)) static struct page *srmmu_pmd_page(pmd_t pmd)
{

	if (srmmu_device_memory(pmd_val(pmd)))
		BUG();
	return pfn_to_page((pmd_val(pmd) & SRMMU_PTD_PMASK) >> (PAGE_SHIFT-4));
}