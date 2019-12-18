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
typedef  int /*<<< orphan*/  pmdval_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  native_make_pmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_pfn_to_mfn (int /*<<< orphan*/ ) ; 

pmd_t xen_make_pmd(pmdval_t pmd)
{
	pmd = pte_pfn_to_mfn(pmd);
	return native_make_pmd(pmd);
}