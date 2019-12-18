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
struct iscsi_session {int dummy; } ;
struct iscsi_conn {struct iscsi_session* session; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
#define  STOP_CONN_RECOVER 129 
#define  STOP_CONN_TERM 128 
 int /*<<< orphan*/  iscsi_conn_printk (int /*<<< orphan*/ ,struct iscsi_conn*,char*,int) ; 
 int /*<<< orphan*/  iscsi_start_session_recovery (struct iscsi_session*,struct iscsi_conn*,int) ; 

void iscsi_conn_stop(struct iscsi_cls_conn *cls_conn, int flag)
{
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct iscsi_session *session = conn->session;

	switch (flag) {
	case STOP_CONN_RECOVER:
	case STOP_CONN_TERM:
		iscsi_start_session_recovery(session, conn, flag);
		break;
	default:
		iscsi_conn_printk(KERN_ERR, conn,
				  "invalid stop flag %d\n", flag);
	}
}