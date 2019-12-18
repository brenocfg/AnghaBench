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

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_probes (void*) ; 
 void* tracepoint_remove_probe (char const*,void*) ; 
 int /*<<< orphan*/  tracepoint_update_probes () ; 
 int /*<<< orphan*/  tracepoints_mutex ; 

int tracepoint_probe_unregister(const char *name, void *probe)
{
	void *old;

	mutex_lock(&tracepoints_mutex);
	old = tracepoint_remove_probe(name, probe);
	mutex_unlock(&tracepoints_mutex);
	if (IS_ERR(old))
		return PTR_ERR(old);

	tracepoint_update_probes();		/* may update entry */
	release_probes(old);
	return 0;
}