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
struct l2cap_disconn_req {void* scid; void* dcid; } ;
struct l2cap_conn {int dummy; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_2__ {int /*<<< orphan*/  scid; int /*<<< orphan*/  dcid; } ;

/* Variables and functions */
 int /*<<< orphan*/  L2CAP_DISCONN_REQ ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_get_ident (struct l2cap_conn*) ; 
 TYPE_1__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  l2cap_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct l2cap_disconn_req*) ; 

__attribute__((used)) static void l2cap_send_disconn_req(struct l2cap_conn *conn, struct sock *sk)
{
	struct l2cap_disconn_req req;

	req.dcid = cpu_to_le16(l2cap_pi(sk)->dcid);
	req.scid = cpu_to_le16(l2cap_pi(sk)->scid);
	l2cap_send_cmd(conn, l2cap_get_ident(conn),
			L2CAP_DISCONN_REQ, sizeof(req), &req);
}