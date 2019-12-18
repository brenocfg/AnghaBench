#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mb_cache_entry {TYPE_1__* e_indexes; int /*<<< orphan*/  e_cache; int /*<<< orphan*/  e_block_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  o_list; } ;

/* Variables and functions */
 scalar_t__ __mb_cache_entry_is_hashed (struct mb_cache_entry*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int mb_cache_indexes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
__mb_cache_entry_unhash(struct mb_cache_entry *ce)
{
	int n;

	if (__mb_cache_entry_is_hashed(ce)) {
		list_del_init(&ce->e_block_list);
		for (n=0; n<mb_cache_indexes(ce->e_cache); n++)
			list_del(&ce->e_indexes[n].o_list);
	}
}