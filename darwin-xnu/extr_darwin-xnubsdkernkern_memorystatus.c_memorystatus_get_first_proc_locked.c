#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * proc_t ;
struct TYPE_3__ {int /*<<< orphan*/  list; } ;
typedef  TYPE_1__ memstat_bucket_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 unsigned int MEMSTAT_BUCKET_COUNT ; 
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 TYPE_1__* memstat_bucket ; 

__attribute__((used)) static proc_t memorystatus_get_first_proc_locked(unsigned int *bucket_index, boolean_t search) {
	memstat_bucket_t *current_bucket;
	proc_t next_p;

	if ((*bucket_index) >= MEMSTAT_BUCKET_COUNT) {
		return NULL;
	}

	current_bucket = &memstat_bucket[*bucket_index];
	next_p = TAILQ_FIRST(&current_bucket->list);
	if (!next_p && search) {
		while (!next_p && (++(*bucket_index) < MEMSTAT_BUCKET_COUNT)) {
			current_bucket = &memstat_bucket[*bucket_index];
			next_p = TAILQ_FIRST(&current_bucket->list);
		}
	}
	
	return next_p;
}