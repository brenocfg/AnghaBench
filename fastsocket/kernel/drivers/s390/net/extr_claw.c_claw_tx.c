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
struct sk_buff {int dummy; } ;
struct net_device {struct claw_privbk* ml_priv; } ;
struct claw_privbk {struct chbk* channel; } ;
struct chbk {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAW_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CLAW_DBF_TEXT_ (int,int /*<<< orphan*/ ,char*,int) ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 size_t WRITE ; 
 int claw_hw_tx (struct sk_buff*,struct net_device*,int) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static int
claw_tx(struct sk_buff *skb, struct net_device *dev)
{
        int             rc;
	struct claw_privbk *privptr = dev->ml_priv;
	unsigned long saveflags;
        struct chbk *p_ch;

	CLAW_DBF_TEXT(4, trace, "claw_tx");
        p_ch=&privptr->channel[WRITE];
        spin_lock_irqsave(get_ccwdev_lock(p_ch->cdev), saveflags);
        rc=claw_hw_tx( skb, dev, 1 );
        spin_unlock_irqrestore(get_ccwdev_lock(p_ch->cdev), saveflags);
	CLAW_DBF_TEXT_(4, trace, "clawtx%d", rc);
	if (rc)
		rc = NETDEV_TX_BUSY;
	else
		rc = NETDEV_TX_OK;
        return rc;
}