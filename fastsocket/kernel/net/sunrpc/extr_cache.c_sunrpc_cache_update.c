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
struct cache_head {int /*<<< orphan*/  expiry_time; struct cache_head* next; int /*<<< orphan*/  flags; } ;
struct cache_detail {int /*<<< orphan*/  hash_lock; int /*<<< orphan*/  entries; int /*<<< orphan*/  (* update ) (struct cache_head*,struct cache_head*) ;struct cache_head** hash_table; int /*<<< orphan*/  (* init ) (struct cache_head*,struct cache_head*) ;struct cache_head* (* alloc ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_NEGATIVE ; 
 int /*<<< orphan*/  CACHE_VALID ; 
 int /*<<< orphan*/  cache_fresh_locked (struct cache_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_fresh_unlocked (struct cache_head*,struct cache_detail*) ; 
 int /*<<< orphan*/  cache_get (struct cache_head*) ; 
 int /*<<< orphan*/  cache_init (struct cache_head*) ; 
 int /*<<< orphan*/  cache_put (struct cache_head*,struct cache_detail*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct cache_head*,struct cache_head*) ; 
 struct cache_head* stub2 () ; 
 int /*<<< orphan*/  stub3 (struct cache_head*,struct cache_head*) ; 
 int /*<<< orphan*/  stub4 (struct cache_head*,struct cache_head*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

struct cache_head *sunrpc_cache_update(struct cache_detail *detail,
				       struct cache_head *new, struct cache_head *old, int hash)
{
	/* The 'old' entry is to be replaced by 'new'.
	 * If 'old' is not VALID, we update it directly,
	 * otherwise we need to replace it
	 */
	struct cache_head **head;
	struct cache_head *tmp;

	if (!test_bit(CACHE_VALID, &old->flags)) {
		write_lock(&detail->hash_lock);
		if (!test_bit(CACHE_VALID, &old->flags)) {
			if (test_bit(CACHE_NEGATIVE, &new->flags))
				set_bit(CACHE_NEGATIVE, &old->flags);
			else
				detail->update(old, new);
			cache_fresh_locked(old, new->expiry_time);
			write_unlock(&detail->hash_lock);
			cache_fresh_unlocked(old, detail);
			return old;
		}
		write_unlock(&detail->hash_lock);
	}
	/* We need to insert a new entry */
	tmp = detail->alloc();
	if (!tmp) {
		cache_put(old, detail);
		return NULL;
	}
	cache_init(tmp);
	detail->init(tmp, old);
	head = &detail->hash_table[hash];

	write_lock(&detail->hash_lock);
	if (test_bit(CACHE_NEGATIVE, &new->flags))
		set_bit(CACHE_NEGATIVE, &tmp->flags);
	else
		detail->update(tmp, new);
	tmp->next = *head;
	*head = tmp;
	detail->entries++;
	cache_get(tmp);
	cache_fresh_locked(tmp, new->expiry_time);
	cache_fresh_locked(old, 0);
	write_unlock(&detail->hash_lock);
	cache_fresh_unlocked(tmp, detail);
	cache_fresh_unlocked(old, detail);
	cache_put(old, detail);
	return tmp;
}