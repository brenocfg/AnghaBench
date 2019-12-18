#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iscsi_task {int dummy; } ;
struct iscsi_session {int /*<<< orphan*/  lock; } ;
struct iscsi_conn {int dummy; } ;
struct cqe {int dummy; } ;
struct bnx2i_nop_in_msg {int itt; } ;
struct bnx2i_conn {TYPE_1__* cls_conn; } ;
struct TYPE_2__ {struct iscsi_conn* dd_data; } ;

/* Variables and functions */
 int ISCSI_NOP_IN_MSG_INDEX ; 
 int /*<<< orphan*/  __iscsi_put_task (struct iscsi_task*) ; 
 struct iscsi_task* iscsi_itt_to_task (struct iscsi_conn*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnx2i_process_nopin_local_cmpl(struct iscsi_session *session,
					   struct bnx2i_conn *bnx2i_conn,
					   struct cqe *cqe)
{
	struct iscsi_conn *conn = bnx2i_conn->cls_conn->dd_data;
	struct bnx2i_nop_in_msg *nop_in;
	struct iscsi_task *task;

	nop_in = (struct bnx2i_nop_in_msg *)cqe;
	spin_lock(&session->lock);
	task = iscsi_itt_to_task(conn,
				 nop_in->itt & ISCSI_NOP_IN_MSG_INDEX);
	if (task)
		__iscsi_put_task(task);
	spin_unlock(&session->lock);
}