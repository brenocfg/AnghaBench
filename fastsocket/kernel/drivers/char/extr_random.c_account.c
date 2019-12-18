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
struct entropy_store {int entropy_count; int /*<<< orphan*/  lock; scalar_t__ limit; int /*<<< orphan*/  name; TYPE_1__* poolinfo; } ;
struct TYPE_2__ {int POOLBITS; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DEBUG_ENT (char*,size_t,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  POLL_OUT ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  fasync ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  random_write_wait ; 
 int random_write_wakeup_thresh ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t account(struct entropy_store *r, size_t nbytes, int min,
		      int reserved)
{
	unsigned long flags;

	/* Hold lock while accounting */
	spin_lock_irqsave(&r->lock, flags);

	BUG_ON(r->entropy_count > r->poolinfo->POOLBITS);
	DEBUG_ENT("trying to extract %d bits from %s\n",
		  nbytes * 8, r->name);

	/* Can we pull enough? */
	if (r->entropy_count / 8 < min + reserved) {
		nbytes = 0;
	} else {
		/* If limited, never pull more than available */
		if (r->limit && nbytes + reserved >= r->entropy_count / 8)
			nbytes = r->entropy_count/8 - reserved;

		if (r->entropy_count / 8 >= nbytes + reserved)
			r->entropy_count -= nbytes*8;
		else
			r->entropy_count = reserved;

		if (r->entropy_count < random_write_wakeup_thresh) {
			wake_up_interruptible(&random_write_wait);
			kill_fasync(&fasync, SIGIO, POLL_OUT);
		}
	}

	DEBUG_ENT("debiting %d entropy credits from %s%s\n",
		  nbytes * 8, r->name, r->limit ? "" : " (unlimited)");

	spin_unlock_irqrestore(&r->lock, flags);

	return nbytes;
}