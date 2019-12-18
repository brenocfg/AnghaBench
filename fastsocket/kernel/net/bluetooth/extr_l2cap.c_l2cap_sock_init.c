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
struct sock {int /*<<< orphan*/  sk_type; } ;
struct l2cap_pinfo {int /*<<< orphan*/  flush_to; scalar_t__ conf_len; scalar_t__ force_reliable; scalar_t__ role_switch; int /*<<< orphan*/  sec_level; int /*<<< orphan*/  fcs; int /*<<< orphan*/  mode; scalar_t__ omtu; int /*<<< orphan*/  imtu; } ;
struct TYPE_2__ {int /*<<< orphan*/  defer_setup; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sock*) ; 
 int /*<<< orphan*/  BT_SECURITY_LOW ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2CAP_DEFAULT_FLUSH_TO ; 
 int /*<<< orphan*/  L2CAP_DEFAULT_MTU ; 
 int /*<<< orphan*/  L2CAP_FCS_CRC16 ; 
 int /*<<< orphan*/  L2CAP_MODE_BASIC ; 
 int /*<<< orphan*/  SREJ_LIST (struct sock*) ; 
 int /*<<< orphan*/  SREJ_QUEUE (struct sock*) ; 
 int /*<<< orphan*/  TX_QUEUE (struct sock*) ; 
 TYPE_1__* bt_sk (struct sock*) ; 
 struct l2cap_pinfo* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2cap_sock_init(struct sock *sk, struct sock *parent)
{
	struct l2cap_pinfo *pi = l2cap_pi(sk);

	BT_DBG("sk %p", sk);

	if (parent) {
		sk->sk_type = parent->sk_type;
		bt_sk(sk)->defer_setup = bt_sk(parent)->defer_setup;

		pi->imtu = l2cap_pi(parent)->imtu;
		pi->omtu = l2cap_pi(parent)->omtu;
		pi->mode = l2cap_pi(parent)->mode;
		pi->fcs  = l2cap_pi(parent)->fcs;
		pi->sec_level = l2cap_pi(parent)->sec_level;
		pi->role_switch = l2cap_pi(parent)->role_switch;
		pi->force_reliable = l2cap_pi(parent)->force_reliable;
	} else {
		pi->imtu = L2CAP_DEFAULT_MTU;
		pi->omtu = 0;
		pi->mode = L2CAP_MODE_BASIC;
		pi->fcs  = L2CAP_FCS_CRC16;
		pi->sec_level = BT_SECURITY_LOW;
		pi->role_switch = 0;
		pi->force_reliable = 0;
	}

	/* Default config options */
	pi->conf_len = 0;
	pi->flush_to = L2CAP_DEFAULT_FLUSH_TO;
	skb_queue_head_init(TX_QUEUE(sk));
	skb_queue_head_init(SREJ_QUEUE(sk));
	INIT_LIST_HEAD(SREJ_LIST(sk));
}