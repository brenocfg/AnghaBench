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
struct TYPE_3__ {int param; int /*<<< orphan*/  len; int /*<<< orphan*/  cid; int /*<<< orphan*/  sid; } ;
struct TYPE_4__ {TYPE_1__ set_param; } ;
struct iscsi_uevent {TYPE_2__ u; } ;
struct iscsi_transport {int (* set_param ) (struct iscsi_cls_conn*,int,char*,int /*<<< orphan*/ ) ;} ;
struct iscsi_cls_session {int recovery_tmo; } ;
struct iscsi_cls_conn {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ISCSI_PARAM_SESS_RECOVERY_TMO 128 
 struct iscsi_cls_conn* iscsi_conn_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iscsi_cls_session* iscsi_session_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*) ; 
 int stub1 (struct iscsi_cls_conn*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iscsi_set_param(struct iscsi_transport *transport, struct iscsi_uevent *ev)
{
	char *data = (char*)ev + sizeof(*ev);
	struct iscsi_cls_conn *conn;
	struct iscsi_cls_session *session;
	int err = 0, value = 0;

	session = iscsi_session_lookup(ev->u.set_param.sid);
	conn = iscsi_conn_lookup(ev->u.set_param.sid, ev->u.set_param.cid);
	if (!conn || !session)
		return -EINVAL;

	switch (ev->u.set_param.param) {
	case ISCSI_PARAM_SESS_RECOVERY_TMO:
		sscanf(data, "%d", &value);
		session->recovery_tmo = value;
		break;
	default:
		err = transport->set_param(conn, ev->u.set_param.param,
					   data, ev->u.set_param.len);
	}

	return err;
}