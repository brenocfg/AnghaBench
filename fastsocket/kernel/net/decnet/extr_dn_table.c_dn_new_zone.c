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
struct dn_zone {int dz_divisor; int dz_hashmask; int dz_order; struct dn_zone* dz_next; int /*<<< orphan*/  dz_mask; int /*<<< orphan*/  dz_hash; } ;
struct dn_hash {struct dn_zone** dh_zones; struct dn_zone* dh_zone_list; } ;
struct dn_fib_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dn_fib_tables_lock ; 
 int /*<<< orphan*/  dnet_make_mask (int) ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dn_zone*) ; 
 struct dn_zone* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dn_zone *dn_new_zone(struct dn_hash *table, int z)
{
	int i;
	struct dn_zone *dz = kzalloc(sizeof(struct dn_zone), GFP_KERNEL);
	if (!dz)
		return NULL;

	if (z) {
		dz->dz_divisor = 16;
		dz->dz_hashmask = 0x0F;
	} else {
		dz->dz_divisor = 1;
		dz->dz_hashmask = 0;
	}

	dz->dz_hash = kcalloc(dz->dz_divisor, sizeof(struct dn_fib_node *), GFP_KERNEL);
	if (!dz->dz_hash) {
		kfree(dz);
		return NULL;
	}

	dz->dz_order = z;
	dz->dz_mask = dnet_make_mask(z);

	for(i = z + 1; i <= 16; i++)
		if (table->dh_zones[i])
			break;

	write_lock_bh(&dn_fib_tables_lock);
	if (i>16) {
		dz->dz_next = table->dh_zone_list;
		table->dh_zone_list = dz;
	} else {
		dz->dz_next = table->dh_zones[i]->dz_next;
		table->dh_zones[i]->dz_next = dz;
	}
	table->dh_zones[z] = dz;
	write_unlock_bh(&dn_fib_tables_lock);
	return dz;
}