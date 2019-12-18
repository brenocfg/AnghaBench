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
struct lec_vcc_priv {int /*<<< orphan*/  old_pop; scalar_t__ xoff; } ;
struct lec_priv {int /*<<< orphan*/  lec_arp_lock; struct atm_vcc* mcast_vcc; } ;
struct lec_arp_table {int /*<<< orphan*/  old_push; struct atm_vcc* vcc; int /*<<< orphan*/  flags; int /*<<< orphan*/  status; int /*<<< orphan*/  atm_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  prv; } ;
struct TYPE_4__ {TYPE_1__ sas_addr; } ;
struct atm_vcc {int /*<<< orphan*/  push; TYPE_2__ remote; int /*<<< orphan*/  pop; struct lec_vcc_priv* user_back; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_ESA_LEN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ESI_FORWARD_DIRECT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LEC_PERMANENT_FLAG ; 
 int /*<<< orphan*/  kfree (struct lec_vcc_priv*) ; 
 struct lec_vcc_priv* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lec_arp_add (struct lec_priv*,struct lec_arp_table*) ; 
 int /*<<< orphan*/  lec_pop ; 
 int /*<<< orphan*/  lec_push ; 
 struct lec_arp_table* make_entry (struct lec_priv*,unsigned char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int lec_mcast_make(struct lec_priv *priv, struct atm_vcc *vcc)
{
	unsigned long flags;
	unsigned char mac_addr[] = {
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff
	};
	struct lec_arp_table *to_add;
	struct lec_vcc_priv *vpriv;
	int err = 0;

	if (!(vpriv = kmalloc(sizeof(struct lec_vcc_priv), GFP_KERNEL)))
		return -ENOMEM;
	vpriv->xoff = 0;
	vpriv->old_pop = vcc->pop;
	vcc->user_back = vpriv;
	vcc->pop = lec_pop;
	spin_lock_irqsave(&priv->lec_arp_lock, flags);
	to_add = make_entry(priv, mac_addr);
	if (!to_add) {
		vcc->pop = vpriv->old_pop;
		kfree(vpriv);
		err = -ENOMEM;
		goto out;
	}
	memcpy(to_add->atm_addr, vcc->remote.sas_addr.prv, ATM_ESA_LEN);
	to_add->status = ESI_FORWARD_DIRECT;
	to_add->flags |= LEC_PERMANENT_FLAG;
	to_add->vcc = vcc;
	to_add->old_push = vcc->push;
	vcc->push = lec_push;
	priv->mcast_vcc = vcc;
	lec_arp_add(priv, to_add);
out:
	spin_unlock_irqrestore(&priv->lec_arp_lock, flags);
	return err;
}