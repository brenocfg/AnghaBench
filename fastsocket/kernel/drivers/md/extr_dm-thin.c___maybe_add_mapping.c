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
struct pool {int /*<<< orphan*/  prepared_mappings; } ;
struct dm_thin_new_mapping {int /*<<< orphan*/  list; scalar_t__ prepared; scalar_t__ quiesced; TYPE_1__* tc; } ;
struct TYPE_2__ {struct pool* pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_worker (struct pool*) ; 

__attribute__((used)) static void __maybe_add_mapping(struct dm_thin_new_mapping *m)
{
	struct pool *pool = m->tc->pool;

	if (m->quiesced && m->prepared) {
		list_add_tail(&m->list, &pool->prepared_mappings);
		wake_worker(pool);
	}
}