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
struct cache_head {struct cache_head* next; } ;
struct cache_detail {int /*<<< orphan*/  hash_lock; int /*<<< orphan*/  entries; scalar_t__ (* match ) (struct cache_head*,struct cache_head*) ;int /*<<< orphan*/  (* init ) (struct cache_head*,struct cache_head*) ;struct cache_head* (* alloc ) () ;struct cache_head** hash_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_get (struct cache_head*) ; 
 int /*<<< orphan*/  cache_init (struct cache_head*) ; 
 scalar_t__ cache_is_expired (struct cache_detail*,struct cache_head*) ; 
 int /*<<< orphan*/  cache_put (struct cache_head*,struct cache_detail*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct cache_head*,struct cache_head*) ; 
 struct cache_head* stub2 () ; 
 int /*<<< orphan*/  stub3 (struct cache_head*,struct cache_head*) ; 
 scalar_t__ stub4 (struct cache_head*,struct cache_head*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

struct cache_head *sunrpc_cache_lookup(struct cache_detail *detail,
				       struct cache_head *key, int hash)
{
	struct cache_head **head,  **hp;
	struct cache_head *new = NULL, *freeme = NULL;

	head = &detail->hash_table[hash];

	read_lock(&detail->hash_lock);

	for (hp=head; *hp != NULL ; hp = &(*hp)->next) {
		struct cache_head *tmp = *hp;
		if (detail->match(tmp, key)) {
			if (cache_is_expired(detail, tmp))
				/* This entry is expired, we will discard it. */
				break;
			cache_get(tmp);
			read_unlock(&detail->hash_lock);
			return tmp;
		}
	}
	read_unlock(&detail->hash_lock);
	/* Didn't find anything, insert an empty entry */

	new = detail->alloc();
	if (!new)
		return NULL;
	/* must fully initialise 'new', else
	 * we might get lose if we need to
	 * cache_put it soon.
	 */
	cache_init(new);
	detail->init(new, key);

	write_lock(&detail->hash_lock);

	/* check if entry appeared while we slept */
	for (hp=head; *hp != NULL ; hp = &(*hp)->next) {
		struct cache_head *tmp = *hp;
		if (detail->match(tmp, key)) {
			if (cache_is_expired(detail, tmp)) {
				*hp = tmp->next;
				tmp->next = NULL;
				detail->entries --;
				freeme = tmp;
				break;
			}
			cache_get(tmp);
			write_unlock(&detail->hash_lock);
			cache_put(new, detail);
			return tmp;
		}
	}
	new->next = *head;
	*head = new;
	detail->entries++;
	cache_get(new);
	write_unlock(&detail->hash_lock);

	if (freeme)
		cache_put(freeme, detail);
	return new;
}