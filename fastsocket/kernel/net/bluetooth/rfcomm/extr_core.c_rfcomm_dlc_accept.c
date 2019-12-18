#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct rfcomm_dlc {int /*<<< orphan*/  v24_sig; int /*<<< orphan*/  dlci; TYPE_3__* session; scalar_t__ role_switch; int /*<<< orphan*/  (* state_change ) (struct rfcomm_dlc*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  state; } ;
struct TYPE_9__ {TYPE_1__* conn; } ;
struct TYPE_8__ {TYPE_2__* sock; } ;
struct TYPE_7__ {struct sock* sk; } ;
struct TYPE_6__ {int /*<<< orphan*/  hcon; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  hci_conn_switch_role (int /*<<< orphan*/ ,int) ; 
 TYPE_5__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  rfcomm_dlc_clear_timer (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_dlc_lock (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_dlc_unlock (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_send_msc (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_send_ua (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct rfcomm_dlc*,int /*<<< orphan*/ ) ; 

void rfcomm_dlc_accept(struct rfcomm_dlc *d)
{
	struct sock *sk = d->session->sock->sk;

	BT_DBG("dlc %p", d);

	rfcomm_send_ua(d->session, d->dlci);

	rfcomm_dlc_clear_timer(d);

	rfcomm_dlc_lock(d);
	d->state = BT_CONNECTED;
	d->state_change(d, 0);
	rfcomm_dlc_unlock(d);

	if (d->role_switch)
		hci_conn_switch_role(l2cap_pi(sk)->conn->hcon, 0x00);

	rfcomm_send_msc(d->session, 1, d->dlci, d->v24_sig);
}