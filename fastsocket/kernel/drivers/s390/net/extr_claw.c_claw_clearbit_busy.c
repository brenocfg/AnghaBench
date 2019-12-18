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
struct net_device {scalar_t__ ml_priv; } ;
struct claw_privbk {int /*<<< orphan*/  tbusy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,void*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static inline void
claw_clearbit_busy(int nr,struct net_device *dev)
{
	clear_bit(nr, (void *)&(((struct claw_privbk *)dev->ml_priv)->tbusy));
	netif_wake_queue(dev);
}