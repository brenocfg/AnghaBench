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
 int /*<<< orphan*/  pgd_dtor ; 
 int /*<<< orphan*/  quicklist_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void pgd_free(struct mm_struct *mm, pgd_t *pgd)
{
	/* in the non-PAE case, clear_page_tables() clears user pgd entries */
 	quicklist_free(0, pgd_dtor, pgd);
}