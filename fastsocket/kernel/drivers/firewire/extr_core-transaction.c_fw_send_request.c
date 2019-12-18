#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  callback; } ;
struct fw_transaction {int node_id; int tlabel; TYPE_2__ packet; int /*<<< orphan*/  link; void* callback_data; int /*<<< orphan*/  (* callback ) (struct fw_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ;} ;
struct fw_card {int current_tlabel; unsigned long long tlabel_mask; TYPE_1__* driver; int /*<<< orphan*/  lock; int /*<<< orphan*/  transaction_list; int /*<<< orphan*/  node_id; int /*<<< orphan*/  flush_timer; } ;
typedef  int /*<<< orphan*/  (* fw_transaction_callback_t ) (struct fw_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ;
struct TYPE_4__ {int /*<<< orphan*/  (* send_request ) (struct fw_card*,TYPE_2__*) ;} ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  RCODE_SEND_ERROR ; 
 int /*<<< orphan*/  fw_fill_request (TYPE_2__*,int,int,int,int /*<<< orphan*/ ,int,int,unsigned long long,void*,size_t) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct fw_card*,TYPE_2__*) ; 
 int /*<<< orphan*/  transmit_complete_callback ; 

void fw_send_request(struct fw_card *card, struct fw_transaction *t, int tcode,
		     int destination_id, int generation, int speed,
		     unsigned long long offset, void *payload, size_t length,
		     fw_transaction_callback_t callback, void *callback_data)
{
	unsigned long flags;
	int tlabel;

	/*
	 * Bump the flush timer up 100ms first of all so we
	 * don't race with a flush timer callback.
	 */

	mod_timer(&card->flush_timer, jiffies + DIV_ROUND_UP(HZ, 10));

	/*
	 * Allocate tlabel from the bitmap and put the transaction on
	 * the list while holding the card spinlock.
	 */

	spin_lock_irqsave(&card->lock, flags);

	tlabel = card->current_tlabel;
	if (card->tlabel_mask & (1ULL << tlabel)) {
		spin_unlock_irqrestore(&card->lock, flags);
		callback(card, RCODE_SEND_ERROR, NULL, 0, callback_data);
		return;
	}

	card->current_tlabel = (card->current_tlabel + 1) & 0x3f;
	card->tlabel_mask |= (1ULL << tlabel);

	t->node_id = destination_id;
	t->tlabel = tlabel;
	t->callback = callback;
	t->callback_data = callback_data;

	fw_fill_request(&t->packet, tcode, t->tlabel,
			destination_id, card->node_id, generation,
			speed, offset, payload, length);
	t->packet.callback = transmit_complete_callback;

	list_add_tail(&t->link, &card->transaction_list);

	spin_unlock_irqrestore(&card->lock, flags);

	card->driver->send_request(card, &t->packet);
}