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
struct neighbour {struct neighbour* next; int /*<<< orphan*/  dev; int /*<<< orphan*/  primary_key; } ;
struct neigh_table {int hash_mask; unsigned int (* hash ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct neighbour** hash_buckets; int /*<<< orphan*/  hash_rnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  NEIGH_CACHE_STAT_INC (struct neigh_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hash_grows ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned long) ; 
 struct neighbour** neigh_hash_alloc (unsigned long) ; 
 int /*<<< orphan*/  neigh_hash_free (struct neighbour**,unsigned int) ; 
 unsigned int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void neigh_hash_grow(struct neigh_table *tbl, unsigned long new_entries)
{
	struct neighbour **new_hash, **old_hash;
	unsigned int i, new_hash_mask, old_entries;

	NEIGH_CACHE_STAT_INC(tbl, hash_grows);

	BUG_ON(!is_power_of_2(new_entries));
	new_hash = neigh_hash_alloc(new_entries);
	if (!new_hash)
		return;

	old_entries = tbl->hash_mask + 1;
	new_hash_mask = new_entries - 1;
	old_hash = tbl->hash_buckets;

	get_random_bytes(&tbl->hash_rnd, sizeof(tbl->hash_rnd));
	for (i = 0; i < old_entries; i++) {
		struct neighbour *n, *next;

		for (n = old_hash[i]; n; n = next) {
			unsigned int hash_val = tbl->hash(n->primary_key, n->dev);

			hash_val &= new_hash_mask;
			next = n->next;

			n->next = new_hash[hash_val];
			new_hash[hash_val] = n;
		}
	}
	tbl->hash_buckets = new_hash;
	tbl->hash_mask = new_hash_mask;

	neigh_hash_free(old_hash, old_entries);
}