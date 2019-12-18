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
 int lt_elem_list_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wq_prepost_rlink(struct wq_prepost *parent, struct wq_prepost *child)
{
	return lt_elem_list_link(&g_prepost_table, &parent->wqte, &child->wqte);
}