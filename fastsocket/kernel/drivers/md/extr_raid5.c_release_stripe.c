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
struct stripe_head {int /*<<< orphan*/  count; struct r5conf* raid_conf; } ;
struct r5conf {int /*<<< orphan*/  device_lock; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_release_stripe (struct r5conf*,struct stripe_head*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_stripe(struct stripe_head *sh)
{
	struct r5conf *conf = sh->raid_conf;
	unsigned long flags;

	local_irq_save(flags);
	if (atomic_dec_and_lock(&sh->count, &conf->device_lock)) {
		do_release_stripe(conf, sh);
		spin_unlock(&conf->device_lock);
	}
	local_irq_restore(flags);
}