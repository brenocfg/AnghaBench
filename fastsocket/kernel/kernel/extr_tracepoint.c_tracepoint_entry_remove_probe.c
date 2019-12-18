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
struct tracepoint_entry {void** funcs; int refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 void** allocate_probes (int) ; 
 int /*<<< orphan*/  debug_print_probes (struct tracepoint_entry*) ; 

__attribute__((used)) static void *
tracepoint_entry_remove_probe(struct tracepoint_entry *entry, void *probe)
{
	int nr_probes = 0, nr_del = 0, i;
	void **old, **new;

	old = entry->funcs;

	if (!old)
		return ERR_PTR(-ENOENT);

	debug_print_probes(entry);
	/* (N -> M), (N > 1, M >= 0) probes */
	for (nr_probes = 0; old[nr_probes]; nr_probes++) {
		if ((!probe || old[nr_probes] == probe))
			nr_del++;
	}

	if (nr_probes - nr_del == 0) {
		/* N -> 0, (N > 1) */
		entry->funcs = NULL;
		entry->refcount = 0;
		debug_print_probes(entry);
		return old;
	} else {
		int j = 0;
		/* N -> M, (N > 1, M > 0) */
		/* + 1 for NULL */
		new = allocate_probes(nr_probes - nr_del + 1);
		if (new == NULL)
			return ERR_PTR(-ENOMEM);
		for (i = 0; old[i]; i++)
			if ((probe && old[i] != probe))
				new[j++] = old[i];
		new[nr_probes - nr_del] = NULL;
		entry->refcount = nr_probes - nr_del;
		entry->funcs = new;
	}
	debug_print_probes(entry);
	return old;
}