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
typedef  int /*<<< orphan*/  pgdval_t ;
struct TYPE_3__ {int /*<<< orphan*/  pgd; } ;
typedef  TYPE_1__ pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  pte_mfn_to_pfn (int /*<<< orphan*/ ) ; 

pgdval_t xen_pgd_val(pgd_t pgd)
{
	return pte_mfn_to_pfn(pgd.pgd);
}