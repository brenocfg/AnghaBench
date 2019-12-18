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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct dlm_lkb {int lkb_flags; int /*<<< orphan*/  lkb_astqueue; int /*<<< orphan*/  lkb_ref; } ;

/* Variables and functions */
 int DLM_IFL_USER ; 
 int /*<<< orphan*/  WAKE_ASTS ; 
 int /*<<< orphan*/  ast_queue ; 
 int /*<<< orphan*/  ast_queue_lock ; 
 scalar_t__ ast_seq_count ; 
 int /*<<< orphan*/  astd_task ; 
 int /*<<< orphan*/  astd_wakeflags ; 
 int dlm_add_lkb_callback (struct dlm_lkb*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dlm_user_add_ast (struct dlm_lkb*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

void dlm_add_ast(struct dlm_lkb *lkb, uint32_t flags, int mode, int status,
		 uint32_t sbflags)
{
	uint64_t seq;
	int rv;

	spin_lock(&ast_queue_lock);

	seq = ++ast_seq_count;

	if (lkb->lkb_flags & DLM_IFL_USER) {
		spin_unlock(&ast_queue_lock);
		dlm_user_add_ast(lkb, flags, mode, status, sbflags, seq);
		return;
	}

	rv = dlm_add_lkb_callback(lkb, flags, mode, status, sbflags, seq);
	if (rv < 0) {
		spin_unlock(&ast_queue_lock);
		return;
	}

	if (list_empty(&lkb->lkb_astqueue)) {
		kref_get(&lkb->lkb_ref);
		list_add_tail(&lkb->lkb_astqueue, &ast_queue);
	}
	spin_unlock(&ast_queue_lock);

	set_bit(WAKE_ASTS, &astd_wakeflags);
	wake_up_process(astd_task);
}