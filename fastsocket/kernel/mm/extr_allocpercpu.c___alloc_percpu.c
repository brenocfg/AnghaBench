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
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t SMP_CACHE_BYTES ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 void* __percpu_disguise (void*) ; 
 int /*<<< orphan*/  __percpu_populate_mask (void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_line_size () ; 
 int /*<<< orphan*/  cpu_possible_map ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int nr_cpu_ids ; 
 size_t roundup (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void *__alloc_percpu(size_t size, size_t align)
{
	/*
	 * We allocate whole cache lines to avoid false sharing
	 */
	size_t sz = roundup(nr_cpu_ids * sizeof(void *), cache_line_size());
	void *pdata = kzalloc(sz, GFP_KERNEL);
	void *__pdata = __percpu_disguise(pdata);

	/*
	 * Can't easily make larger alignment work with kmalloc.  WARN
	 * on it.  Larger alignment should only be used for module
	 * percpu sections on SMP for which this path isn't used.
	 */
	WARN_ON_ONCE(align > SMP_CACHE_BYTES);

	if (unlikely(!pdata))
		return NULL;
	if (likely(!__percpu_populate_mask(__pdata, size, GFP_KERNEL,
					   &cpu_possible_map)))
		return __pdata;
	kfree(pdata);
	return NULL;
}