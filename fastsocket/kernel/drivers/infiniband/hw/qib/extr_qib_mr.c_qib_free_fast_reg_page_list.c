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
struct ib_fast_reg_page_list {struct ib_fast_reg_page_list* page_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ib_fast_reg_page_list*) ; 

void qib_free_fast_reg_page_list(struct ib_fast_reg_page_list *pl)
{
	kfree(pl->page_list);
	kfree(pl);
}