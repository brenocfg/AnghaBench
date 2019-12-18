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
struct futex_q {int /*<<< orphan*/ * lock_ptr; int /*<<< orphan*/  key; } ;
struct futex_hash_bucket {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_futex_key_refs (int /*<<< orphan*/ *) ; 
 struct futex_hash_bucket* hash_futex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct futex_hash_bucket *queue_lock(struct futex_q *q)
{
	struct futex_hash_bucket *hb;

	get_futex_key_refs(&q->key);
	hb = hash_futex(&q->key);
	q->lock_ptr = &hb->lock;

	spin_lock(&hb->lock);
	return hb;
}