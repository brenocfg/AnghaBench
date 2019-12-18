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
struct entropy_store {int last_data_init; TYPE_1__* poolinfo; int /*<<< orphan*/  lock; scalar_t__ entropy_count; } ;
typedef  int /*<<< orphan*/  now ;
typedef  unsigned long ktime_t ;
typedef  int /*<<< orphan*/  flags ;
struct TYPE_2__ {int poolwords; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_get_random_long (unsigned long*) ; 
 unsigned long ktime_get_real () ; 
 int /*<<< orphan*/  mix_pool_bytes (struct entropy_store*,unsigned long*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long* utsname () ; 

__attribute__((used)) static void init_std_data(struct entropy_store *r)
{
	int i;
	ktime_t now;
	unsigned long flags;

	spin_lock_irqsave(&r->lock, flags);
	r->entropy_count = 0;
	r->last_data_init = false;
	spin_unlock_irqrestore(&r->lock, flags);

	now = ktime_get_real();
	mix_pool_bytes(r, &now, sizeof(now));
	for (i = r->poolinfo->poolwords; i; i--) {
		if (!arch_get_random_long(&flags))
			break;
		mix_pool_bytes(r, &flags, sizeof(flags));
	}
	mix_pool_bytes(r, utsname(), sizeof(*(utsname())));
}