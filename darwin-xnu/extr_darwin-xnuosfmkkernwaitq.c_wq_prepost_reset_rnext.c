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
struct wq_prepost {int /*<<< orphan*/  wqte; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_prepost_table ; 
 int /*<<< orphan*/  lt_elem_list_break (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wq_prepost_reset_rnext(struct wq_prepost *wqp)
{
	(void)lt_elem_list_break(&g_prepost_table, &wqp->wqte);
}