#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * function; } ;
struct IsdnCardState {TYPE_3__ dbusytimer; int /*<<< orphan*/  (* cardmsg ) (struct IsdnCardState*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* DC_Close ) (struct IsdnCardState*) ;int /*<<< orphan*/ * tx_skb; int /*<<< orphan*/ * rcvbuf; int /*<<< orphan*/  sq; int /*<<< orphan*/  rq; TYPE_1__* bcs; } ;
struct TYPE_7__ {struct IsdnCardState* cs; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* BC_Close ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_RELEASE ; 
 TYPE_4__* cards ; 
 int /*<<< orphan*/  del_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ll_unload (struct IsdnCardState*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub3 (struct IsdnCardState*) ; 
 int /*<<< orphan*/  stub4 (struct IsdnCardState*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void closecard(int cardnr)
{
	struct IsdnCardState *csta = cards[cardnr].cs;

	if (csta->bcs->BC_Close != NULL) {
		csta->bcs->BC_Close(csta->bcs + 1);
		csta->bcs->BC_Close(csta->bcs);
	}

	skb_queue_purge(&csta->rq);
	skb_queue_purge(&csta->sq);
	kfree(csta->rcvbuf);
	csta->rcvbuf = NULL;
	if (csta->tx_skb) {
		dev_kfree_skb(csta->tx_skb);
		csta->tx_skb = NULL;
	}
	if (csta->DC_Close != NULL) {
		csta->DC_Close(csta);
	}
	if (csta->cardmsg)
		csta->cardmsg(csta, CARD_RELEASE, NULL);
	if (csta->dbusytimer.function != NULL) // FIXME?
		del_timer(&csta->dbusytimer);
	ll_unload(csta);
}