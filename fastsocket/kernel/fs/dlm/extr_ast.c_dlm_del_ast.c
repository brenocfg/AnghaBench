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
struct dlm_lkb {int /*<<< orphan*/  lkb_astqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ast_queue_lock ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void dlm_del_ast(struct dlm_lkb *lkb)
{
	spin_lock(&ast_queue_lock);
	if (!list_empty(&lkb->lkb_astqueue))
		list_del_init(&lkb->lkb_astqueue);
	spin_unlock(&ast_queue_lock);
}