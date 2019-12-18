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
typedef  union futex_key {int dummy; } futex_key ;
struct TYPE_4__ {int /*<<< orphan*/ * lock; } ;
struct TYPE_5__ {TYPE_1__ plist; } ;
struct futex_q {union futex_key key; TYPE_2__ list; int /*<<< orphan*/ * lock_ptr; } ;
struct futex_hash_bucket {int /*<<< orphan*/  lock; int /*<<< orphan*/  chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_futex_key_refs (union futex_key*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  plist_add (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plist_del (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline
void requeue_futex(struct futex_q *q, struct futex_hash_bucket *hb1,
		   struct futex_hash_bucket *hb2, union futex_key *key2)
{

	/*
	 * If key1 and key2 hash to the same bucket, no need to
	 * requeue.
	 */
	if (likely(&hb1->chain != &hb2->chain)) {
		plist_del(&q->list, &hb1->chain);
		plist_add(&q->list, &hb2->chain);
		q->lock_ptr = &hb2->lock;
#ifdef CONFIG_DEBUG_PI_LIST
		q->list.plist.lock = &hb2->lock;
#endif
	}
	get_futex_key_refs(key2);
	q->key = *key2;
}