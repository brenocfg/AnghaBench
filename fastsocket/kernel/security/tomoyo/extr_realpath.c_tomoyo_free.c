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
 int /*<<< orphan*/  atomic_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (void const*) ; 
 int /*<<< orphan*/  ksize (void const*) ; 
 int /*<<< orphan*/  tomoyo_dynamic_memory_size ; 

void tomoyo_free(const void *p)
{
	if (p) {
		atomic_sub(ksize(p), &tomoyo_dynamic_memory_size);
		kfree(p);
	}
}