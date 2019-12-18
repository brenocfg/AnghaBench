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
struct net_device {scalar_t__ ml_priv; } ;
struct claw_privbk {scalar_t__ write_free_count; int /*<<< orphan*/ * p_write_active_first; } ;
struct chbk {scalar_t__ claw_state; int /*<<< orphan*/  collect_queue; scalar_t__ ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAW_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ CLAW_STOP ; 
 int /*<<< orphan*/  claw_free_wrt_buf (struct net_device*) ; 
 int claw_hw_tx (struct sk_buff*,struct net_device*,int) ; 
 struct sk_buff* claw_pack_skb (struct claw_privbk*) ; 
 int /*<<< orphan*/  claw_strt_out_IO (struct net_device*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static void
claw_write_next ( struct chbk * p_ch )
{

        struct net_device  *dev;
        struct claw_privbk *privptr=NULL;
	struct sk_buff *pk_skb;
	int	rc;

	CLAW_DBF_TEXT(4, trace, "claw_wrt");
        if (p_ch->claw_state == CLAW_STOP)
                return;
        dev = (struct net_device *) p_ch->ndev;
	privptr = (struct claw_privbk *) dev->ml_priv;
        claw_free_wrt_buf( dev );
	if ((privptr->write_free_count > 0) &&
	    !skb_queue_empty(&p_ch->collect_queue)) {
	  	pk_skb = claw_pack_skb(privptr);
		while (pk_skb != NULL) {
			rc = claw_hw_tx( pk_skb, dev,1);
			if (privptr->write_free_count > 0) {
	   			pk_skb = claw_pack_skb(privptr);
			} else
				pk_skb = NULL;
		}
	}
        if (privptr->p_write_active_first!=NULL) {
                claw_strt_out_IO(dev);
        }
        return;
}