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
struct dn_zone {int dz_divisor; int dz_nent; int /*<<< orphan*/  dz_order; int /*<<< orphan*/ * dz_hash; struct dn_zone* dz_next; } ;
struct dn_hash {struct dn_zone* dh_zone_list; } ;
struct dn_fib_table {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ dn_fib_hash_zombies ; 
 scalar_t__ dn_flush_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dn_hash*) ; 

__attribute__((used)) static int dn_fib_table_flush(struct dn_fib_table *tb)
{
	struct dn_hash *table = (struct dn_hash *)tb->data;
	struct dn_zone *dz;
	int found = 0;

	dn_fib_hash_zombies = 0;
	for(dz = table->dh_zone_list; dz; dz = dz->dz_next) {
		int i;
		int tmp = 0;
		for(i = dz->dz_divisor-1; i >= 0; i--)
			tmp += dn_flush_list(&dz->dz_hash[i], dz->dz_order, table);
		dz->dz_nent -= tmp;
		found += tmp;
	}

	return found;
}