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
typedef  int u_char ;
struct net_local {int state; int /*<<< orphan*/  csr1; scalar_t__ framelen; scalar_t__ tx_frameno; scalar_t__ wait_frameno; scalar_t__ outpos; scalar_t__ inppos; int /*<<< orphan*/  timer_ticks; } ;
struct net_device {scalar_t__ base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANGE_LEVEL_START_TICKS ; 
 scalar_t__ CSR0 ; 
 scalar_t__ CSR1 ; 
 int EN_INT ; 
 int FL_NEED_RESEND ; 
 int FL_PREV_OK ; 
 int FL_WAIT_ACK ; 
 int PR_RES ; 
 struct net_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void
card_start( struct net_device  *dev )
{
	struct net_local  *nl = netdev_priv(dev);

	nl->timer_ticks = CHANGE_LEVEL_START_TICKS;
	nl->state &= ~(FL_WAIT_ACK | FL_NEED_RESEND);
	nl->state |= FL_PREV_OK;

	nl->inppos = nl->outpos = 0;
	nl->wait_frameno = 0;
	nl->tx_frameno	 = 0;
	nl->framelen	 = 0;

	outb( *(u_char *)&nl->csr1 | PR_RES, dev->base_addr + CSR1 );
	outb( EN_INT, dev->base_addr + CSR0 );
}