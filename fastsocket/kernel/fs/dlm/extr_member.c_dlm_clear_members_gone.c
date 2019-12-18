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
struct dlm_ls {int /*<<< orphan*/  ls_nodes_gone; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_memb_list (int /*<<< orphan*/ *) ; 

void dlm_clear_members_gone(struct dlm_ls *ls)
{
	clear_memb_list(&ls->ls_nodes_gone);
}