#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pmdval_t ;
struct TYPE_3__ {int /*<<< orphan*/  pmd; } ;
typedef  TYPE_1__ pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  pte_mfn_to_pfn (int /*<<< orphan*/ ) ; 

pmdval_t xen_pmd_val(pmd_t pmd)
{
	return pte_mfn_to_pfn(pmd.pmd);
}