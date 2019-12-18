#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  queue; } ;
struct iscsi_session {TYPE_1__ cmdpool; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct iscsi_conn {char* data; TYPE_2__* login_task; int /*<<< orphan*/  ehwait; TYPE_3__ tmf_timer; int /*<<< orphan*/  xmitwork; int /*<<< orphan*/  requeue; int /*<<< orphan*/  cmdqueue; int /*<<< orphan*/  mgmtqueue; TYPE_3__ transport_timer; int /*<<< orphan*/  tmf_state; scalar_t__ exp_statsn; int /*<<< orphan*/  id; int /*<<< orphan*/  c_stage; struct iscsi_cls_conn* cls_conn; struct iscsi_session* session; struct iscsi_conn* dd_data; } ;
struct iscsi_cls_session {struct iscsi_session* dd_data; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
struct TYPE_5__ {char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISCSI_CONN_INITIAL_STAGE ; 
 int /*<<< orphan*/  ISCSI_DEF_MAX_RECV_SEG_LEN ; 
 int /*<<< orphan*/  TMF_INITIAL ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __kfifo_get (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  __kfifo_put (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_check_transport_timeouts ; 
 struct iscsi_cls_conn* iscsi_create_conn (struct iscsi_cls_session*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_destroy_conn (struct iscsi_cls_conn*) ; 
 int /*<<< orphan*/  iscsi_xmitworker ; 
 int /*<<< orphan*/  memset (struct iscsi_conn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

struct iscsi_cls_conn *
iscsi_conn_setup(struct iscsi_cls_session *cls_session, int dd_size,
		 uint32_t conn_idx)
{
	struct iscsi_session *session = cls_session->dd_data;
	struct iscsi_conn *conn;
	struct iscsi_cls_conn *cls_conn;
	char *data;

	cls_conn = iscsi_create_conn(cls_session, sizeof(*conn) + dd_size,
				     conn_idx);
	if (!cls_conn)
		return NULL;
	conn = cls_conn->dd_data;
	memset(conn, 0, sizeof(*conn) + dd_size);

	conn->dd_data = cls_conn->dd_data + sizeof(*conn);
	conn->session = session;
	conn->cls_conn = cls_conn;
	conn->c_stage = ISCSI_CONN_INITIAL_STAGE;
	conn->id = conn_idx;
	conn->exp_statsn = 0;
	conn->tmf_state = TMF_INITIAL;

	init_timer(&conn->transport_timer);
	conn->transport_timer.data = (unsigned long)conn;
	conn->transport_timer.function = iscsi_check_transport_timeouts;

	INIT_LIST_HEAD(&conn->mgmtqueue);
	INIT_LIST_HEAD(&conn->cmdqueue);
	INIT_LIST_HEAD(&conn->requeue);
	INIT_WORK(&conn->xmitwork, iscsi_xmitworker);

	/* allocate login_task used for the login/text sequences */
	spin_lock_bh(&session->lock);
	if (!__kfifo_get(session->cmdpool.queue,
                         (void*)&conn->login_task,
			 sizeof(void*))) {
		spin_unlock_bh(&session->lock);
		goto login_task_alloc_fail;
	}
	spin_unlock_bh(&session->lock);

	data = (char *) __get_free_pages(GFP_KERNEL,
					 get_order(ISCSI_DEF_MAX_RECV_SEG_LEN));
	if (!data)
		goto login_task_data_alloc_fail;
	conn->login_task->data = conn->data = data;

	init_timer(&conn->tmf_timer);
	init_waitqueue_head(&conn->ehwait);

	return cls_conn;

login_task_data_alloc_fail:
	__kfifo_put(session->cmdpool.queue, (void*)&conn->login_task,
		    sizeof(void*));
login_task_alloc_fail:
	iscsi_destroy_conn(cls_conn);
	return NULL;
}