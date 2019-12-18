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
struct tracepoint_entry {int /*<<< orphan*/  refcount; } ;
struct tracepoint {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_tracepoint (struct tracepoint*) ; 
 struct tracepoint_entry* get_tracepoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_tracepoint (struct tracepoint_entry**,struct tracepoint*,int) ; 
 int /*<<< orphan*/  tracepoints_mutex ; 

void
tracepoint_update_probe_range(struct tracepoint *begin, struct tracepoint *end)
{
	struct tracepoint *iter;
	struct tracepoint_entry *mark_entry;

	if (!begin)
		return;

	mutex_lock(&tracepoints_mutex);
	for (iter = begin; iter < end; iter++) {
		mark_entry = get_tracepoint(iter->name);
		if (mark_entry) {
			set_tracepoint(&mark_entry, iter,
					!!mark_entry->refcount);
		} else {
			disable_tracepoint(iter);
		}
	}
	mutex_unlock(&tracepoints_mutex);
}