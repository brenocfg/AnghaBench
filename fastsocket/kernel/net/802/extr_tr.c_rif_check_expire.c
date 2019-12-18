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
struct rif_cache {int last_used; struct rif_cache* next; } ;

/* Variables and functions */
 int RIF_TABLE_SIZE ; 
 int jiffies ; 
 int /*<<< orphan*/  kfree (struct rif_cache*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rif_lock ; 
 struct rif_cache** rif_table ; 
 int /*<<< orphan*/  rif_timer ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int sysctl_tr_rif_timeout ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 scalar_t__ time_before_eq (unsigned long,int) ; 

__attribute__((used)) static void rif_check_expire(unsigned long dummy)
{
	int i;
	unsigned long flags, next_interval = jiffies + sysctl_tr_rif_timeout/2;

	spin_lock_irqsave(&rif_lock, flags);

	for(i =0; i < RIF_TABLE_SIZE; i++) {
		struct rif_cache *entry, **pentry;

		pentry = rif_table+i;
		while((entry=*pentry) != NULL) {
			unsigned long expires
				= entry->last_used + sysctl_tr_rif_timeout;

			if (time_before_eq(expires, jiffies)) {
				*pentry = entry->next;
				kfree(entry);
			} else {
				pentry = &entry->next;

				if (time_before(expires, next_interval))
					next_interval = expires;
			}
		}
	}

	spin_unlock_irqrestore(&rif_lock, flags);

	mod_timer(&rif_timer, next_interval);

}