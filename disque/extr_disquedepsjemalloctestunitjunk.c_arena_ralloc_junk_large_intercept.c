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
 int /*<<< orphan*/  arena_ralloc_junk_large_orig (void*,size_t,size_t) ; 
 int /*<<< orphan*/  assert_zu_eq (size_t,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  large_maxclass ; 
 void* most_recently_trimmed ; 
 int /*<<< orphan*/  shrink_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
arena_ralloc_junk_large_intercept(void *ptr, size_t old_usize, size_t usize)
{

	arena_ralloc_junk_large_orig(ptr, old_usize, usize);
	assert_zu_eq(old_usize, large_maxclass, "Unexpected old_usize");
	assert_zu_eq(usize, shrink_size(large_maxclass), "Unexpected usize");
	most_recently_trimmed = ptr;
}