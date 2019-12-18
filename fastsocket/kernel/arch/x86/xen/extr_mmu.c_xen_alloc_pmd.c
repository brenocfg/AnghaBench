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
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PT_PMD ; 
 int /*<<< orphan*/  xen_alloc_ptpage (struct mm_struct*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xen_alloc_pmd(struct mm_struct *mm, unsigned long pfn)
{
	xen_alloc_ptpage(mm, pfn, PT_PMD);
}