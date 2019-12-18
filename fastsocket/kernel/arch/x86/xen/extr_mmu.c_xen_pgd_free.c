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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/ * xen_get_user_pgd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xen_pgd_free(struct mm_struct *mm, pgd_t *pgd)
{
#ifdef CONFIG_X86_64
	pgd_t *user_pgd = xen_get_user_pgd(pgd);

	if (user_pgd)
		free_page((unsigned long)user_pgd);
#endif
}