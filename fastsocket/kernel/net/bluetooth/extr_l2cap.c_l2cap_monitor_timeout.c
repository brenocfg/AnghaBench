#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct sock {int dummy; } ;
struct TYPE_3__ {scalar_t__ retry_count; scalar_t__ remote_max_tx; int /*<<< orphan*/  conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  L2CAP_CTRL_POLL ; 
 int /*<<< orphan*/  __mod_monitor_timer () ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 TYPE_1__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  l2cap_send_disconn_req (int /*<<< orphan*/ ,struct sock*) ; 
 int /*<<< orphan*/  l2cap_send_rr_or_rnr (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2cap_monitor_timeout(unsigned long arg)
{
	struct sock *sk = (void *) arg;
	u16 control;

	bh_lock_sock(sk);
	if (l2cap_pi(sk)->retry_count >= l2cap_pi(sk)->remote_max_tx) {
		l2cap_send_disconn_req(l2cap_pi(sk)->conn, sk);
		return;
	}

	l2cap_pi(sk)->retry_count++;
	__mod_monitor_timer();

	control = L2CAP_CTRL_POLL;
	l2cap_send_rr_or_rnr(l2cap_pi(sk), control);
	bh_unlock_sock(sk);
}