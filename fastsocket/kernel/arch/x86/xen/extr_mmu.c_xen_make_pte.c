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
typedef  int /*<<< orphan*/  pteval_t ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  native_make_pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_pfn_to_mfn (int /*<<< orphan*/ ) ; 

pte_t xen_make_pte(pteval_t pte)
{
	pte = pte_pfn_to_mfn(pte);
	return native_make_pte(pte);
}