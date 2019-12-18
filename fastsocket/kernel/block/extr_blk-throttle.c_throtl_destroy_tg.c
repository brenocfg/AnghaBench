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
struct throtl_data {int /*<<< orphan*/  nr_undestroyed_grps; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throtl_put_tg (struct throtl_grp*) ; 

__attribute__((used)) static void
throtl_destroy_tg(struct throtl_data *td, struct throtl_grp *tg)
{
	/* Something wrong if we are trying to remove same group twice */
	BUG_ON(hlist_unhashed(&tg->tg_node));

	hlist_del_init(&tg->tg_node);

	/*
	 * Put the reference taken at the time of creation so that when all
	 * queues are gone, group can be destroyed.
	 */
	throtl_put_tg(tg);
	td->nr_undestroyed_grps--;
}