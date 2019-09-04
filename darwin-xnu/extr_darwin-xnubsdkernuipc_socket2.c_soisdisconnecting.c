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
struct socket {int so_state; int /*<<< orphan*/  so_timeo; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  SO_FILT_HINT_LOCKED ; 
 int SS_CANTRCVMORE ; 
 int SS_CANTSENDMORE ; 
 int SS_ISCONNECTING ; 
 int SS_ISDISCONNECTING ; 
 int /*<<< orphan*/  sflt_notify (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_evt_disconnecting ; 
 int /*<<< orphan*/  soevent (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sorwakeup (struct socket*) ; 
 int /*<<< orphan*/  sowwakeup (struct socket*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

void
soisdisconnecting(struct socket *so)
{
	so->so_state &= ~SS_ISCONNECTING;
	so->so_state |= (SS_ISDISCONNECTING|SS_CANTRCVMORE|SS_CANTSENDMORE);
	soevent(so, SO_FILT_HINT_LOCKED);
	sflt_notify(so, sock_evt_disconnecting, NULL);
	wakeup((caddr_t)&so->so_timeo);
	sowwakeup(so);
	sorwakeup(so);
}