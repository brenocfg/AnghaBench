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
typedef  int /*<<< orphan*/  u32 ;
struct tgt_ring {int /*<<< orphan*/  tr_lock; int /*<<< orphan*/  tr_idx; } ;
struct TYPE_2__ {int status; int /*<<< orphan*/  type; } ;
struct tgt_event {TYPE_1__ hdr; } ;

/* Variables and functions */
 int BUSY ; 
 int /*<<< orphan*/  flush_dcache_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  memcpy (struct tgt_event*,struct tgt_event*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct tgt_event* tgt_head_event (struct tgt_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tgt_poll_wait ; 
 int /*<<< orphan*/  tgt_ring_idx_inc (struct tgt_ring*) ; 
 struct tgt_ring tx_ring ; 
 int /*<<< orphan*/  virt_to_page (struct tgt_event*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tgt_uspace_send_event(u32 type, struct tgt_event *p)
{
	struct tgt_event *ev;
	struct tgt_ring *ring = &tx_ring;
	unsigned long flags;
	int err = 0;

	spin_lock_irqsave(&ring->tr_lock, flags);

	ev = tgt_head_event(ring, ring->tr_idx);
	if (!ev->hdr.status)
		tgt_ring_idx_inc(ring);
	else
		err = -BUSY;

	spin_unlock_irqrestore(&ring->tr_lock, flags);

	if (err)
		return err;

	memcpy(ev, p, sizeof(*ev));
	ev->hdr.type = type;
	mb();
	ev->hdr.status = 1;

	flush_dcache_page(virt_to_page(ev));

	wake_up_interruptible(&tgt_poll_wait);

	return 0;
}