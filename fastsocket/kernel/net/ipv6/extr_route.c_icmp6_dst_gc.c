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
struct dst_entry {struct dst_entry* next; int /*<<< orphan*/  __refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_free (struct dst_entry*) ; 
 struct dst_entry* icmp6_dst_gc_list ; 
 int /*<<< orphan*/  icmp6_dst_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int icmp6_dst_gc(void)
{
	struct dst_entry *dst, *next, **pprev;
	int more = 0;

	next = NULL;

	spin_lock_bh(&icmp6_dst_lock);
	pprev = &icmp6_dst_gc_list;

	while ((dst = *pprev) != NULL) {
		if (!atomic_read(&dst->__refcnt)) {
			*pprev = dst->next;
			dst_free(dst);
		} else {
			pprev = &dst->next;
			++more;
		}
	}

	spin_unlock_bh(&icmp6_dst_lock);

	return more;
}