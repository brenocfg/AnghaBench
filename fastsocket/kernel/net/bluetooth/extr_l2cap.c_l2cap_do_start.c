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
struct sock {int dummy; } ;
struct l2cap_info_req {void* type; int /*<<< orphan*/  psm; void* scid; } ;
struct l2cap_conn_req {void* type; int /*<<< orphan*/  psm; void* scid; } ;
struct l2cap_conn {int info_state; void* info_ident; int /*<<< orphan*/  info_timer; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_2__ {void* ident; int /*<<< orphan*/  psm; int /*<<< orphan*/  scid; struct l2cap_conn* conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  L2CAP_CONN_REQ ; 
 int L2CAP_INFO_FEAT_MASK_REQ_DONE ; 
 int L2CAP_INFO_FEAT_MASK_REQ_SENT ; 
 int /*<<< orphan*/  L2CAP_INFO_REQ ; 
 int /*<<< orphan*/  L2CAP_INFO_TIMEOUT ; 
 int /*<<< orphan*/  L2CAP_IT_FEAT_MASK ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ l2cap_check_security (struct sock*) ; 
 void* l2cap_get_ident (struct l2cap_conn*) ; 
 TYPE_1__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  l2cap_send_cmd (struct l2cap_conn*,void*,int /*<<< orphan*/ ,int,struct l2cap_info_req*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2cap_do_start(struct sock *sk)
{
	struct l2cap_conn *conn = l2cap_pi(sk)->conn;

	if (conn->info_state & L2CAP_INFO_FEAT_MASK_REQ_SENT) {
		if (!(conn->info_state & L2CAP_INFO_FEAT_MASK_REQ_DONE))
			return;

		if (l2cap_check_security(sk)) {
			struct l2cap_conn_req req;
			req.scid = cpu_to_le16(l2cap_pi(sk)->scid);
			req.psm  = l2cap_pi(sk)->psm;

			l2cap_pi(sk)->ident = l2cap_get_ident(conn);

			l2cap_send_cmd(conn, l2cap_pi(sk)->ident,
					L2CAP_CONN_REQ, sizeof(req), &req);
		}
	} else {
		struct l2cap_info_req req;
		req.type = cpu_to_le16(L2CAP_IT_FEAT_MASK);

		conn->info_state |= L2CAP_INFO_FEAT_MASK_REQ_SENT;
		conn->info_ident = l2cap_get_ident(conn);

		mod_timer(&conn->info_timer, jiffies +
					msecs_to_jiffies(L2CAP_INFO_TIMEOUT));

		l2cap_send_cmd(conn, conn->info_ident,
					L2CAP_INFO_REQ, sizeof(req), &req);
	}
}