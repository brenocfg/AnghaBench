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
struct iscsi_session {scalar_t__ state; int /*<<< orphan*/  lock; struct iscsi_conn* leadconn; } ;
struct iscsi_conn {TYPE_1__* cls_conn; } ;
struct device {int dummy; } ;
typedef  enum iscsi_err { ____Placeholder_iscsi_err } iscsi_err ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ISCSI_ERR_INVALID_HOST ; 
 scalar_t__ ISCSI_STATE_TERMINATE ; 
 struct device* get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_conn_error_event (TYPE_1__*,int) ; 
 int /*<<< orphan*/  iscsi_conn_failure (struct iscsi_conn*,int) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void iscsi_session_failure(struct iscsi_session *session,
			   enum iscsi_err err)
{
	struct iscsi_conn *conn;
	struct device *dev;

	spin_lock_bh(&session->lock);
	conn = session->leadconn;
	if (session->state == ISCSI_STATE_TERMINATE || !conn) {
		spin_unlock_bh(&session->lock);
		return;
	}

	dev = get_device(&conn->cls_conn->dev);
	spin_unlock_bh(&session->lock);
	if (!dev)
	        return;
	/*
	 * if the host is being removed bypass the connection
	 * recovery initialization because we are going to kill
	 * the session.
	 */
	if (err == ISCSI_ERR_INVALID_HOST)
		iscsi_conn_error_event(conn->cls_conn, err);
	else
		iscsi_conn_failure(conn, err);
	put_device(dev);
}