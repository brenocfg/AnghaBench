#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tgt_ring {int tr_idx; int /*<<< orphan*/  tr_lock; } ;
struct TYPE_2__ {scalar_t__ status; } ;
struct tgt_event {TYPE_1__ hdr; } ;
struct poll_table_struct {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 unsigned int POLLIN ; 
 unsigned int POLLRDNORM ; 
 int TGT_MAX_EVENTS ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct tgt_event* tgt_head_event (struct tgt_ring*,int) ; 
 int /*<<< orphan*/  tgt_poll_wait ; 
 struct tgt_ring tx_ring ; 

__attribute__((used)) static unsigned int tgt_poll(struct file * file, struct poll_table_struct *wait)
{
	struct tgt_event *ev;
	struct tgt_ring *ring = &tx_ring;
	unsigned long flags;
	unsigned int mask = 0;
	u32 idx;

	poll_wait(file, &tgt_poll_wait, wait);

	spin_lock_irqsave(&ring->tr_lock, flags);

	idx = ring->tr_idx ? ring->tr_idx - 1 : TGT_MAX_EVENTS - 1;
	ev = tgt_head_event(ring, idx);
	if (ev->hdr.status)
		mask |= POLLIN | POLLRDNORM;

	spin_unlock_irqrestore(&ring->tr_lock, flags);

	return mask;
}