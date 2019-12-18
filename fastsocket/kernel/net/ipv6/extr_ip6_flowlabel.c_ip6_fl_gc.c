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
struct ip6_flowlabel {unsigned long lastuse; unsigned long linger; unsigned long expires; struct ip6_flowlabel* next; int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int FL_HASH_MASK ; 
 unsigned long FL_MAX_LINGER ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fl_free (struct ip6_flowlabel*) ; 
 struct ip6_flowlabel** fl_ht ; 
 int /*<<< orphan*/  fl_size ; 
 int /*<<< orphan*/  ip6_fl_gc_timer ; 
 int /*<<< orphan*/  ip6_fl_lock ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ip6_fl_gc(unsigned long dummy)
{
	int i;
	unsigned long now = jiffies;
	unsigned long sched = 0;

	write_lock(&ip6_fl_lock);

	for (i=0; i<=FL_HASH_MASK; i++) {
		struct ip6_flowlabel *fl, **flp;
		flp = &fl_ht[i];
		while ((fl=*flp) != NULL) {
			if (atomic_read(&fl->users) == 0) {
				unsigned long ttd = fl->lastuse + fl->linger;
				if (time_after(ttd, fl->expires))
					fl->expires = ttd;
				ttd = fl->expires;
				if (time_after_eq(now, ttd)) {
					*flp = fl->next;
					fl_free(fl);
					atomic_dec(&fl_size);
					continue;
				}
				if (!sched || time_before(ttd, sched))
					sched = ttd;
			}
			flp = &fl->next;
		}
	}
	if (!sched && atomic_read(&fl_size))
		sched = now + FL_MAX_LINGER;
	if (sched) {
		mod_timer(&ip6_fl_gc_timer, sched);
	}
	write_unlock(&ip6_fl_lock);
}