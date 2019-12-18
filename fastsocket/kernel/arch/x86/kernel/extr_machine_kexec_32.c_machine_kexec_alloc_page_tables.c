#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * pte1; int /*<<< orphan*/ * pte0; int /*<<< orphan*/ * pmd1; int /*<<< orphan*/ * pmd0; int /*<<< orphan*/ * pgd; } ;
struct kimage {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machine_kexec_free_page_tables (struct kimage*) ; 

__attribute__((used)) static int machine_kexec_alloc_page_tables(struct kimage *image)
{
	image->arch.pgd = (pgd_t *)get_zeroed_page(GFP_KERNEL);
#ifdef CONFIG_X86_PAE
	image->arch.pmd0 = (pmd_t *)get_zeroed_page(GFP_KERNEL);
	image->arch.pmd1 = (pmd_t *)get_zeroed_page(GFP_KERNEL);
#endif
	image->arch.pte0 = (pte_t *)get_zeroed_page(GFP_KERNEL);
	image->arch.pte1 = (pte_t *)get_zeroed_page(GFP_KERNEL);
	if (!image->arch.pgd ||
#ifdef CONFIG_X86_PAE
	    !image->arch.pmd0 || !image->arch.pmd1 ||
#endif
	    !image->arch.pte0 || !image->arch.pte1) {
		machine_kexec_free_page_tables(image);
		return -ENOMEM;
	}
	return 0;
}