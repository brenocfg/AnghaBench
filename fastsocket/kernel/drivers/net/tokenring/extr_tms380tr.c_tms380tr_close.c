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
struct TYPE_3__ {unsigned long data; int /*<<< orphan*/  function; scalar_t__ expires; } ;
struct net_local {int HaltInProgress; int Sleeping; TYPE_1__ timer; scalar_t__ TransmitCommandActive; int /*<<< orphan*/  wait_for_tok_int; } ;
struct net_device {scalar_t__ dma; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  OC_CLOSE ; 
 int /*<<< orphan*/  POSREG ; 
 int /*<<< orphan*/  SIFCMD ; 
 int /*<<< orphan*/  SIFWRITEB (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIFWRITEW (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  del_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  disable_dma (scalar_t__) ; 
 int /*<<< orphan*/  interruptible_sleep_on (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 struct net_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  tms380tr_cancel_tx_queue (struct net_local*) ; 
 int /*<<< orphan*/  tms380tr_disable_interrupts (struct net_device*) ; 
 int /*<<< orphan*/  tms380tr_enable_interrupts (struct net_device*) ; 
 int /*<<< orphan*/  tms380tr_exec_cmd (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tms380tr_timer_end_wait ; 

int tms380tr_close(struct net_device *dev)
{
	struct net_local *tp = netdev_priv(dev);
	netif_stop_queue(dev);
	
	del_timer(&tp->timer);

	/* Flush the Tx and disable Rx here. */

	tp->HaltInProgress 	= 1;
	tms380tr_exec_cmd(dev, OC_CLOSE);
	tp->timer.expires	= jiffies + 1*HZ;
	tp->timer.function 	= tms380tr_timer_end_wait;
	tp->timer.data 		= (unsigned long)dev;
	add_timer(&tp->timer);

	tms380tr_enable_interrupts(dev);

	tp->Sleeping = 1;
	interruptible_sleep_on(&tp->wait_for_tok_int);
	tp->TransmitCommandActive = 0;
    
	del_timer(&tp->timer);
	tms380tr_disable_interrupts(dev);
   
#ifdef CONFIG_ISA
	if(dev->dma > 0) 
	{
		unsigned long flags=claim_dma_lock();
		disable_dma(dev->dma);
		release_dma_lock(flags);
	}
#endif
	
	SIFWRITEW(0xFF00, SIFCMD);
#if 0
	if(dev->dma > 0) /* what the? */
		SIFWRITEB(0xff, POSREG);
#endif
	tms380tr_cancel_tx_queue(tp);

	return (0);
}