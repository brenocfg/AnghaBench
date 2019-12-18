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
struct sk_buff {scalar_t__ cb; } ;
struct irlap_cb {int /*<<< orphan*/  next_bofs; int /*<<< orphan*/  bofs_count; scalar_t__ xbofs_delay; scalar_t__ mtt_required; int /*<<< orphan*/  speed; } ;
struct irda_skb_cb {scalar_t__ xbofs_delay; int /*<<< orphan*/  next_xbofs; int /*<<< orphan*/  xbofs; int /*<<< orphan*/  next_speed; scalar_t__ mtt; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAP_MAGIC ; 

__attribute__((used)) static inline void irlap_insert_info(struct irlap_cb *self,
				     struct sk_buff *skb)
{
	struct irda_skb_cb *cb = (struct irda_skb_cb *) skb->cb;

	/*
	 * Insert MTT (min. turn time) and speed into skb, so that the
	 * device driver knows which settings to use
	 */
	cb->magic = LAP_MAGIC;
	cb->mtt = self->mtt_required;
	cb->next_speed = self->speed;

	/* Reset */
	self->mtt_required = 0;

	/*
	 * Delay equals negotiated BOFs count, plus the number of BOFs to
	 * force the negotiated minimum turnaround time
	 */
	cb->xbofs = self->bofs_count;
	cb->next_xbofs = self->next_bofs;
	cb->xbofs_delay = self->xbofs_delay;

	/* Reset XBOF's delay (used only for getting min turn time) */
	self->xbofs_delay = 0;
	/* Put the correct xbofs value for the next packet */
	self->bofs_count = self->next_bofs;
}