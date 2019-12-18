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
struct fn_zone {int fz_divisor; int fz_hashmask; int fz_order; struct fn_zone* fz_next; int /*<<< orphan*/  fz_mask; int /*<<< orphan*/  fz_hash; } ;
struct fn_hash {struct fn_zone** fn_zones; struct fn_zone* fn_zone_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  fib_hash_genid ; 
 int /*<<< orphan*/  fib_hash_lock ; 
 int /*<<< orphan*/  fz_hash_alloc (int) ; 
 int /*<<< orphan*/  inet_make_mask (int) ; 
 int /*<<< orphan*/  kfree (struct fn_zone*) ; 
 struct fn_zone* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct fn_zone *
fn_new_zone(struct fn_hash *table, int z)
{
	int i;
	struct fn_zone *fz = kzalloc(sizeof(struct fn_zone), GFP_KERNEL);
	if (!fz)
		return NULL;

	if (z) {
		fz->fz_divisor = 16;
	} else {
		fz->fz_divisor = 1;
	}
	fz->fz_hashmask = (fz->fz_divisor - 1);
	fz->fz_hash = fz_hash_alloc(fz->fz_divisor);
	if (!fz->fz_hash) {
		kfree(fz);
		return NULL;
	}
	fz->fz_order = z;
	fz->fz_mask = inet_make_mask(z);

	/* Find the first not empty zone with more specific mask */
	for (i=z+1; i<=32; i++)
		if (table->fn_zones[i])
			break;
	write_lock_bh(&fib_hash_lock);
	if (i>32) {
		/* No more specific masks, we are the first. */
		fz->fz_next = table->fn_zone_list;
		table->fn_zone_list = fz;
	} else {
		fz->fz_next = table->fn_zones[i]->fz_next;
		table->fn_zones[i]->fz_next = fz;
	}
	table->fn_zones[z] = fz;
	fib_hash_genid++;
	write_unlock_bh(&fib_hash_lock);
	return fz;
}