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
typedef  scalar_t__ u32 ;
struct sk_buff {int /*<<< orphan*/  dev; int /*<<< orphan*/  len; } ;
struct frame {scalar_t__ sent_jiffs; int /*<<< orphan*/  sent; scalar_t__ waited_total; scalar_t__ waited; int /*<<< orphan*/  tag; struct sk_buff* skb; } ;
struct aoetgt {TYPE_1__* ifp; int /*<<< orphan*/  nout; } ;
struct TYPE_4__ {int /*<<< orphan*/  function; } ;
struct aoedev {TYPE_2__ timer; int /*<<< orphan*/  rttdev; int /*<<< orphan*/  rttavg; struct aoetgt** tgt; } ;
struct aoe_hdr {int dummy; } ;
struct aoe_atahdr {int scnt; int lba3; int /*<<< orphan*/  cmdstat; } ;
struct TYPE_3__ {int /*<<< orphan*/  nd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CMD_ID_ATA ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  RTTAVG_INIT ; 
 int /*<<< orphan*/  RTTDEV_INIT ; 
 int /*<<< orphan*/  aoehdr_atainit (struct aoedev*,struct aoetgt*,struct aoe_hdr*) ; 
 int /*<<< orphan*/  do_gettimeofday (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fhash (struct frame*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memset (struct aoe_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct frame* newframe (struct aoedev*) ; 
 int /*<<< orphan*/  rexmit_timer ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

struct sk_buff *
aoecmd_ata_id(struct aoedev *d)
{
	struct aoe_hdr *h;
	struct aoe_atahdr *ah;
	struct frame *f;
	struct sk_buff *skb;
	struct aoetgt *t;

	f = newframe(d);
	if (f == NULL)
		return NULL;

	t = *d->tgt;

	/* initialize the headers & frame */
	skb = f->skb;
	h = (struct aoe_hdr *) skb_mac_header(skb);
	ah = (struct aoe_atahdr *) (h+1);
	skb_put(skb, sizeof *h + sizeof *ah);
	memset(h, 0, skb->len);
	f->tag = aoehdr_atainit(d, t, h);
	fhash(f);
	t->nout++;
	f->waited = 0;
	f->waited_total = 0;

	/* set up ata header */
	ah->scnt = 1;
	ah->cmdstat = ATA_CMD_ID_ATA;
	ah->lba3 = 0xa0;

	skb->dev = t->ifp->nd;

	d->rttavg = RTTAVG_INIT;
	d->rttdev = RTTDEV_INIT;
	d->timer.function = rexmit_timer;

	skb = skb_clone(skb, GFP_ATOMIC);
	if (skb) {
		do_gettimeofday(&f->sent);
		f->sent_jiffs = (u32) jiffies;
	}

	return skb;
}