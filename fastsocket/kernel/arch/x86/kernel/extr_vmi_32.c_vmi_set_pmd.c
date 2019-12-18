#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  member_0; int /*<<< orphan*/  pte; } ;
typedef  TYPE_3__ pte_t ;
struct TYPE_10__ {int /*<<< orphan*/  pgd; } ;
struct TYPE_11__ {TYPE_1__ pgd; } ;
struct TYPE_13__ {TYPE_2__ pud; int /*<<< orphan*/  pmd; } ;
typedef  TYPE_4__ pmd_t ;
struct TYPE_14__ {int /*<<< orphan*/  (* set_pte ) (TYPE_3__ const,TYPE_3__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VMI_PAGE_PD ; 
 int /*<<< orphan*/  stub1 (TYPE_3__ const,TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_7__ vmi_ops ; 

__attribute__((used)) static void vmi_set_pmd(pmd_t *pmdp, pmd_t pmdval)
{
#ifdef CONFIG_X86_PAE
	const pte_t pte = { .pte = pmdval.pmd };
#else
	const pte_t pte = { pmdval.pud.pgd.pgd };
#endif
	vmi_ops.set_pte(pte, (pte_t *)pmdp, VMI_PAGE_PD);
}