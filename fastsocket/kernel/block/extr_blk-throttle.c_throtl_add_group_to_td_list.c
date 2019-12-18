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
struct throtl_grp {int /*<<< orphan*/  tg_node; } ;
struct throtl_data {int /*<<< orphan*/  nr_undestroyed_grps; int /*<<< orphan*/  tg_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
throtl_add_group_to_td_list(struct throtl_data *td, struct throtl_grp *tg)
{
	hlist_add_head(&tg->tg_node, &td->tg_list);
	td->nr_undestroyed_grps++;
}