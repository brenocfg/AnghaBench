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
struct fn_zone {int fz_divisor; struct fn_zone* fz_next; } ;
struct fn_hash {struct fn_zone* fn_zone_list; } ;
struct fib_table {scalar_t__ tb_data; } ;

/* Variables and functions */
 scalar_t__ fn_flush_list (struct fn_zone*,int) ; 

__attribute__((used)) static int fn_hash_flush(struct fib_table *tb)
{
	struct fn_hash *table = (struct fn_hash *) tb->tb_data;
	struct fn_zone *fz;
	int found = 0;

	for (fz = table->fn_zone_list; fz; fz = fz->fz_next) {
		int i;

		for (i = fz->fz_divisor - 1; i >= 0; i--)
			found += fn_flush_list(fz, i);
	}
	return found;
}