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
struct se_session {int /*<<< orphan*/  sess_cmd_lock; int /*<<< orphan*/  sess_cmd_list; scalar_t__ sess_tearing_down; } ;
struct se_cmd {int check_release; int /*<<< orphan*/  se_cmd_list; int /*<<< orphan*/  se_cmd_flags; int /*<<< orphan*/  cmd_kref; } ;

/* Variables and functions */
 int ESHUTDOWN ; 
 int /*<<< orphan*/  SCF_ACK_KREF ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int target_get_sess_cmd(struct se_session *se_sess, struct se_cmd *se_cmd,
			       bool ack_kref)
{
	unsigned long flags;
	int ret = 0;

	kref_init(&se_cmd->cmd_kref);
	/*
	 * Add a second kref if the fabric caller is expecting to handle
	 * fabric acknowledgement that requires two target_put_sess_cmd()
	 * invocations before se_cmd descriptor release.
	 */
	if (ack_kref == true) {
		kref_get(&se_cmd->cmd_kref);
		se_cmd->se_cmd_flags |= SCF_ACK_KREF;
	}

	spin_lock_irqsave(&se_sess->sess_cmd_lock, flags);
	if (se_sess->sess_tearing_down) {
		ret = -ESHUTDOWN;
		goto out;
	}
	list_add_tail(&se_cmd->se_cmd_list, &se_sess->sess_cmd_list);
	se_cmd->check_release = 1;

out:
	spin_unlock_irqrestore(&se_sess->sess_cmd_lock, flags);
	return ret;
}