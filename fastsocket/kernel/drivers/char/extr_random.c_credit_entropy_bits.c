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
struct entropy_store {int entropy_count; int /*<<< orphan*/  lock; TYPE_1__* poolinfo; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int POOLBITS; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_ENT (char*,...) ; 
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  fasync ; 
 struct entropy_store input_pool ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  random_read_wait ; 
 int random_read_wakeup_thresh ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void credit_entropy_bits(struct entropy_store *r, int nbits)
{
	unsigned long flags;
	int entropy_count;

	if (!nbits)
		return;

	spin_lock_irqsave(&r->lock, flags);

	DEBUG_ENT("added %d entropy credits to %s\n", nbits, r->name);
	entropy_count = r->entropy_count;
	entropy_count += nbits;
	if (entropy_count < 0) {
		DEBUG_ENT("negative entropy/overflow\n");
		entropy_count = 0;
	} else if (entropy_count > r->poolinfo->POOLBITS)
		entropy_count = r->poolinfo->POOLBITS;
	r->entropy_count = entropy_count;

	/* should we wake readers? */
	if (r == &input_pool && entropy_count >= random_read_wakeup_thresh) {
		wake_up_interruptible(&random_read_wait);
		kill_fasync(&fasync, SIGIO, POLL_IN);
	}
	spin_unlock_irqrestore(&r->lock, flags);
}