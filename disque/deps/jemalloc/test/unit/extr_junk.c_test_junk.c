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
 size_t ZU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arena_dalloc_junk_large ; 
 int /*<<< orphan*/  arena_dalloc_junk_large_intercept ; 
 int /*<<< orphan*/  arena_dalloc_junk_large_orig ; 
 int /*<<< orphan*/  arena_dalloc_junk_small ; 
 int /*<<< orphan*/  arena_dalloc_junk_small_intercept ; 
 int /*<<< orphan*/  arena_dalloc_junk_small_orig ; 
 int /*<<< orphan*/  assert_c_eq (char,int,char*,size_t,size_t) ; 
 int /*<<< orphan*/  assert_ptr_not_null (void*,char*) ; 
 int /*<<< orphan*/  assert_true (int,char*,size_t) ; 
 int /*<<< orphan*/  dallocx (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  huge_dalloc_junk ; 
 int /*<<< orphan*/  huge_dalloc_junk_intercept ; 
 int /*<<< orphan*/  huge_dalloc_junk_orig ; 
 scalar_t__ mallocx (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ opt_junk_alloc ; 
 scalar_t__ opt_junk_free ; 
 scalar_t__ rallocx (char*,size_t,int /*<<< orphan*/ ) ; 
 size_t sallocx (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ saw_junking ; 
 int /*<<< orphan*/  watch_junking (char*) ; 
 size_t xallocx (char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_junk(size_t sz_min, size_t sz_max)
{
	char *s;
	size_t sz_prev, sz, i;

	if (opt_junk_free) {
		arena_dalloc_junk_small_orig = arena_dalloc_junk_small;
		arena_dalloc_junk_small = arena_dalloc_junk_small_intercept;
		arena_dalloc_junk_large_orig = arena_dalloc_junk_large;
		arena_dalloc_junk_large = arena_dalloc_junk_large_intercept;
		huge_dalloc_junk_orig = huge_dalloc_junk;
		huge_dalloc_junk = huge_dalloc_junk_intercept;
	}

	sz_prev = 0;
	s = (char *)mallocx(sz_min, 0);
	assert_ptr_not_null((void *)s, "Unexpected mallocx() failure");

	for (sz = sallocx(s, 0); sz <= sz_max;
	    sz_prev = sz, sz = sallocx(s, 0)) {
		if (sz_prev > 0) {
			assert_c_eq(s[0], 'a',
			    "Previously allocated byte %zu/%zu is corrupted",
			    ZU(0), sz_prev);
			assert_c_eq(s[sz_prev-1], 'a',
			    "Previously allocated byte %zu/%zu is corrupted",
			    sz_prev-1, sz_prev);
		}

		for (i = sz_prev; i < sz; i++) {
			if (opt_junk_alloc) {
				assert_c_eq(s[i], 0xa5,
				    "Newly allocated byte %zu/%zu isn't "
				    "junk-filled", i, sz);
			}
			s[i] = 'a';
		}

		if (xallocx(s, sz+1, 0, 0) == sz) {
			watch_junking(s);
			s = (char *)rallocx(s, sz+1, 0);
			assert_ptr_not_null((void *)s,
			    "Unexpected rallocx() failure");
			assert_true(!opt_junk_free || saw_junking,
			    "Expected region of size %zu to be junk-filled",
			    sz);
		}
	}

	watch_junking(s);
	dallocx(s, 0);
	assert_true(!opt_junk_free || saw_junking,
	    "Expected region of size %zu to be junk-filled", sz);

	if (opt_junk_free) {
		arena_dalloc_junk_small = arena_dalloc_junk_small_orig;
		arena_dalloc_junk_large = arena_dalloc_junk_large_orig;
		huge_dalloc_junk = huge_dalloc_junk_orig;
	}
}