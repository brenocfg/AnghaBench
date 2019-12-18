#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  queue; } ;
struct iscsi_session {int /*<<< orphan*/  lock; struct iscsi_conn* leadconn; TYPE_2__ cmdpool; TYPE_1__* host; int /*<<< orphan*/  state; } ;
struct iscsi_conn {int /*<<< orphan*/  login_task; int /*<<< orphan*/  persistent_address; scalar_t__ data; int /*<<< orphan*/  ehwait; int /*<<< orphan*/  c_stage; int /*<<< orphan*/  transport_timer; struct iscsi_session* session; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_failed; int /*<<< orphan*/  host_busy; int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_CONN_CLEANUP_WAIT ; 
 int /*<<< orphan*/  ISCSI_DEF_MAX_RECV_SEG_LEN ; 
 int /*<<< orphan*/  ISCSI_STATE_TERMINATE ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  __kfifo_put (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_conn_printk (int /*<<< orphan*/ ,struct iscsi_conn*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_destroy_conn (struct iscsi_cls_conn*) ; 
 int /*<<< orphan*/  iscsi_suspend_tx (struct iscsi_conn*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void iscsi_conn_teardown(struct iscsi_cls_conn *cls_conn)
{
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct iscsi_session *session = conn->session;
	unsigned long flags;

	del_timer_sync(&conn->transport_timer);

	spin_lock_bh(&session->lock);
	conn->c_stage = ISCSI_CONN_CLEANUP_WAIT;
	if (session->leadconn == conn) {
		/*
		 * leading connection? then give up on recovery.
		 */
		session->state = ISCSI_STATE_TERMINATE;
		wake_up(&conn->ehwait);
	}
	spin_unlock_bh(&session->lock);

	/*
	 * Block until all in-progress commands for this connection
	 * time out or fail.
	 */
	for (;;) {
		spin_lock_irqsave(session->host->host_lock, flags);
		if (!session->host->host_busy) { /* OK for ERL == 0 */
			spin_unlock_irqrestore(session->host->host_lock, flags);
			break;
		}
		spin_unlock_irqrestore(session->host->host_lock, flags);
		msleep_interruptible(500);
		iscsi_conn_printk(KERN_INFO, conn, "iscsi conn_destroy(): "
				  "host_busy %d host_failed %d\n",
				  session->host->host_busy,
				  session->host->host_failed);
		/*
		 * force eh_abort() to unblock
		 */
		wake_up(&conn->ehwait);
	}

	/* flush queued up work because we free the connection below */
	iscsi_suspend_tx(conn);

	spin_lock_bh(&session->lock);
	free_pages((unsigned long) conn->data,
		   get_order(ISCSI_DEF_MAX_RECV_SEG_LEN));
	kfree(conn->persistent_address);
	__kfifo_put(session->cmdpool.queue, (void*)&conn->login_task,
		    sizeof(void*));
	if (session->leadconn == conn)
		session->leadconn = NULL;
	spin_unlock_bh(&session->lock);

	iscsi_destroy_conn(cls_conn);
}