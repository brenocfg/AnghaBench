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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct jme_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  JME_IEVE ; 
 int /*<<< orphan*/  jme_intr_msi (struct jme_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jread32 (struct jme_adapter*,int /*<<< orphan*/ ) ; 
 struct jme_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static irqreturn_t
jme_msi(int irq, void *dev_id)
{
	struct net_device *netdev = dev_id;
	struct jme_adapter *jme = netdev_priv(netdev);
	u32 intrstat;

	intrstat = jread32(jme, JME_IEVE);

	jme_intr_msi(jme, intrstat);

	return IRQ_HANDLED;
}