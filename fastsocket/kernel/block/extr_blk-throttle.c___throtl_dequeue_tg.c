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
struct throtl_grp {int /*<<< orphan*/  rb_node; } ;
struct throtl_data {int /*<<< orphan*/  tg_service_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  throtl_clear_tg_on_rr (struct throtl_grp*) ; 
 int /*<<< orphan*/  throtl_rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __throtl_dequeue_tg(struct throtl_data *td, struct throtl_grp *tg)
{
	throtl_rb_erase(&tg->rb_node, &td->tg_service_tree);
	throtl_clear_tg_on_rr(tg);
}