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
 int /*<<< orphan*/  SHUT_RDWR ; 
 int SO_FILT_HINT_CONNINFO_UPDATED ; 
 int SO_FILT_HINT_DISCONNECTED ; 
 int SO_FILT_HINT_LOCKED ; 
 int SS_CANTRCVMORE ; 
 int SS_CANTSENDMORE ; 
 int SS_ISCONNECTED ; 
 int SS_ISCONNECTING ; 
 int SS_ISDISCONNECTED ; 
 int SS_ISDISCONNECTING ; 
 int /*<<< orphan*/  cfil_sock_notify_shutdown (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soevent (struct socket*,int) ; 
 int /*<<< orphan*/  sorwakeup (struct socket*) ; 
 int /*<<< orphan*/  sowwakeup (struct socket*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

void
sodisconnectwakeup(struct socket *so)
{
	so->so_state &= ~(SS_ISCONNECTING|SS_ISCONNECTED|SS_ISDISCONNECTING);
	so->so_state |= (SS_CANTRCVMORE|SS_CANTSENDMORE|SS_ISDISCONNECTED);
	soevent(so, SO_FILT_HINT_LOCKED | SO_FILT_HINT_DISCONNECTED |
	    SO_FILT_HINT_CONNINFO_UPDATED);
	wakeup((caddr_t)&so->so_timeo);
	sowwakeup(so);
	sorwakeup(so);

#if CONTENT_FILTER
	/* Notify content filters as soon as we cannot send/receive data */
	cfil_sock_notify_shutdown(so, SHUT_RDWR);
#endif /* CONTENT_FILTER */
}