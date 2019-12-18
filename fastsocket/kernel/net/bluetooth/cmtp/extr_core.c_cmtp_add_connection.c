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
struct socket {int /*<<< orphan*/  sk; } ;
struct cmtp_session {scalar_t__ state; int flags; int /*<<< orphan*/ ** reassembly; int /*<<< orphan*/  transmit; int /*<<< orphan*/  applications; int /*<<< orphan*/  msgnum; int /*<<< orphan*/  wait; struct socket* sock; int /*<<< orphan*/  name; int /*<<< orphan*/  mtu; int /*<<< orphan*/  bdaddr; } ;
struct cmtp_connadd_req {int flags; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_3__ {int /*<<< orphan*/  imtu; int /*<<< orphan*/  omtu; } ;

/* Variables and functions */
 scalar_t__ BT_CONFIG ; 
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int /*<<< orphan*/  CLONE_KERNEL ; 
 int /*<<< orphan*/  CMTP_INITIAL_MSGNUM ; 
 int CMTP_LOOPBACK ; 
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct cmtp_session* __cmtp_get_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __cmtp_link_session (struct cmtp_session*) ; 
 int /*<<< orphan*/  __cmtp_unlink_session (struct cmtp_session*) ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  baswap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* batostr (int /*<<< orphan*/ *) ; 
 TYPE_2__* bt_sk (int /*<<< orphan*/ ) ; 
 int cmtp_attach_device (struct cmtp_session*) ; 
 int /*<<< orphan*/  cmtp_detach_device (struct cmtp_session*) ; 
 int /*<<< orphan*/  cmtp_session ; 
 int /*<<< orphan*/  cmtp_session_sem ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int kernel_thread (int /*<<< orphan*/ ,struct cmtp_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cmtp_session*) ; 
 struct cmtp_session* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* l2cap_pi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  uint ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int cmtp_add_connection(struct cmtp_connadd_req *req, struct socket *sock)
{
	struct cmtp_session *session, *s;
	bdaddr_t src, dst;
	int i, err;

	BT_DBG("");

	baswap(&src, &bt_sk(sock->sk)->src);
	baswap(&dst, &bt_sk(sock->sk)->dst);

	session = kzalloc(sizeof(struct cmtp_session), GFP_KERNEL);
	if (!session)
		return -ENOMEM;

	down_write(&cmtp_session_sem);

	s = __cmtp_get_session(&bt_sk(sock->sk)->dst);
	if (s && s->state == BT_CONNECTED) {
		err = -EEXIST;
		goto failed;
	}

	bacpy(&session->bdaddr, &bt_sk(sock->sk)->dst);

	session->mtu = min_t(uint, l2cap_pi(sock->sk)->omtu, l2cap_pi(sock->sk)->imtu);

	BT_DBG("mtu %d", session->mtu);

	sprintf(session->name, "%s", batostr(&dst));

	session->sock  = sock;
	session->state = BT_CONFIG;

	init_waitqueue_head(&session->wait);

	session->msgnum = CMTP_INITIAL_MSGNUM;

	INIT_LIST_HEAD(&session->applications);

	skb_queue_head_init(&session->transmit);

	for (i = 0; i < 16; i++)
		session->reassembly[i] = NULL;

	session->flags = req->flags;

	__cmtp_link_session(session);

	err = kernel_thread(cmtp_session, session, CLONE_KERNEL);
	if (err < 0)
		goto unlink;

	if (!(session->flags & (1 << CMTP_LOOPBACK))) {
		err = cmtp_attach_device(session);
		if (err < 0)
			goto detach;
	}

	up_write(&cmtp_session_sem);
	return 0;

detach:
	cmtp_detach_device(session);

unlink:
	__cmtp_unlink_session(session);

failed:
	up_write(&cmtp_session_sem);
	kfree(session);
	return err;
}