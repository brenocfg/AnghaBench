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
struct dlm_member {int /*<<< orphan*/  list; } ;
struct dlm_ls {int /*<<< orphan*/  ls_num_nodes; int /*<<< orphan*/  ls_nodes_gone; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dlm_remove_member(struct dlm_ls *ls, struct dlm_member *memb)
{
	list_move(&memb->list, &ls->ls_nodes_gone);
	ls->ls_num_nodes--;
}