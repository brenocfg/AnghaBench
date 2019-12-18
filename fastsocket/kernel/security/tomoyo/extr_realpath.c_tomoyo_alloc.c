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
 int /*<<< orphan*/  atomic_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ksize (void*) ; 
 void* kzalloc (size_t const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tomoyo_dynamic_memory_size ; 

void *tomoyo_alloc(const size_t size)
{
	void *p = kzalloc(size, GFP_KERNEL);
	if (p)
		atomic_add(ksize(p), &tomoyo_dynamic_memory_size);
	return p;
}