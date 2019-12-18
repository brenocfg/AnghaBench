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
 int /*<<< orphan*/  kmemtrace_kfree ; 
 int /*<<< orphan*/  kmemtrace_kmalloc ; 
 int /*<<< orphan*/  kmemtrace_kmalloc_node ; 
 int /*<<< orphan*/  kmemtrace_kmem_cache_alloc ; 
 int /*<<< orphan*/  kmemtrace_kmem_cache_alloc_node ; 
 int /*<<< orphan*/  kmemtrace_kmem_cache_free ; 
 int register_trace_kfree (int /*<<< orphan*/ ) ; 
 int register_trace_kmalloc (int /*<<< orphan*/ ) ; 
 int register_trace_kmalloc_node (int /*<<< orphan*/ ) ; 
 int register_trace_kmem_cache_alloc (int /*<<< orphan*/ ) ; 
 int register_trace_kmem_cache_alloc_node (int /*<<< orphan*/ ) ; 
 int register_trace_kmem_cache_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kmemtrace_start_probes(void)
{
	int err;

	err = register_trace_kmalloc(kmemtrace_kmalloc);
	if (err)
		return err;
	err = register_trace_kmem_cache_alloc(kmemtrace_kmem_cache_alloc);
	if (err)
		return err;
	err = register_trace_kmalloc_node(kmemtrace_kmalloc_node);
	if (err)
		return err;
	err = register_trace_kmem_cache_alloc_node(kmemtrace_kmem_cache_alloc_node);
	if (err)
		return err;
	err = register_trace_kfree(kmemtrace_kfree);
	if (err)
		return err;
	err = register_trace_kmem_cache_free(kmemtrace_kmem_cache_free);

	return err;
}