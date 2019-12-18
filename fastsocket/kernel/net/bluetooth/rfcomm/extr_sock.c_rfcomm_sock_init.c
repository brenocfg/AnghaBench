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
struct sock {int /*<<< orphan*/  sk_type; } ;
struct rfcomm_pinfo {scalar_t__ role_switch; TYPE_1__* dlc; int /*<<< orphan*/  sec_level; } ;
struct TYPE_4__ {scalar_t__ defer_setup; } ;
struct TYPE_3__ {scalar_t__ role_switch; int /*<<< orphan*/  sec_level; scalar_t__ defer_setup; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sock*) ; 
 int /*<<< orphan*/  BT_SECURITY_LOW ; 
 TYPE_2__* bt_sk (struct sock*) ; 
 struct rfcomm_pinfo* rfcomm_pi (struct sock*) ; 

__attribute__((used)) static void rfcomm_sock_init(struct sock *sk, struct sock *parent)
{
	struct rfcomm_pinfo *pi = rfcomm_pi(sk);

	BT_DBG("sk %p", sk);

	if (parent) {
		sk->sk_type = parent->sk_type;
		pi->dlc->defer_setup = bt_sk(parent)->defer_setup;

		pi->sec_level = rfcomm_pi(parent)->sec_level;
		pi->role_switch = rfcomm_pi(parent)->role_switch;
	} else {
		pi->dlc->defer_setup = 0;

		pi->sec_level = BT_SECURITY_LOW;
		pi->role_switch = 0;
	}

	pi->dlc->sec_level = pi->sec_level;
	pi->dlc->role_switch = pi->role_switch;
}