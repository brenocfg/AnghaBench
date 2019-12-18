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
 int FILL_BYTE ; 
 int /*<<< orphan*/  MALLOCX_ZERO ; 
 int /*<<< orphan*/  assert_false (int /*<<< orphan*/ ,char*,size_t,...) ; 
 int /*<<< orphan*/  assert_ptr_not_null (void*,char*) ; 
 int /*<<< orphan*/  assert_zu_eq (int /*<<< orphan*/ ,size_t,char*) ; 
 int /*<<< orphan*/  dallocx (void*,int /*<<< orphan*/ ) ; 
 void* mallocx (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int,size_t) ; 
 size_t nallocx (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_fill (void*,int,size_t,size_t) ; 
 int /*<<< orphan*/  xallocx (void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_zero(size_t szmin, size_t szmax)
{
	size_t sz, nsz;
	void *p;
#define	FILL_BYTE 0x7aU

	sz = szmax;
	p = mallocx(sz, MALLOCX_ZERO);
	assert_ptr_not_null(p, "Unexpected mallocx() error");
	assert_false(validate_fill(p, 0x00, 0, sz), "Memory not filled: sz=%zu",
	    sz);

	/*
	 * Fill with non-zero so that non-debug builds are more likely to detect
	 * errors.
	 */
	memset(p, FILL_BYTE, sz);
	assert_false(validate_fill(p, FILL_BYTE, 0, sz),
	    "Memory not filled: sz=%zu", sz);

	/* Shrink in place so that we can expect growing in place to succeed. */
	sz = szmin;
	assert_zu_eq(xallocx(p, sz, 0, MALLOCX_ZERO), sz,
	    "Unexpected xallocx() error");
	assert_false(validate_fill(p, FILL_BYTE, 0, sz),
	    "Memory not filled: sz=%zu", sz);

	for (sz = szmin; sz < szmax; sz = nsz) {
		nsz = nallocx(sz+1, MALLOCX_ZERO);
		assert_zu_eq(xallocx(p, sz+1, 0, MALLOCX_ZERO), nsz,
		    "Unexpected xallocx() failure");
		assert_false(validate_fill(p, FILL_BYTE, 0, sz),
		    "Memory not filled: sz=%zu", sz);
		assert_false(validate_fill(p, 0x00, sz, nsz-sz),
		    "Memory not filled: sz=%zu, nsz-sz=%zu", sz, nsz-sz);
		memset((void *)((uintptr_t)p + sz), FILL_BYTE, nsz-sz);
		assert_false(validate_fill(p, FILL_BYTE, 0, nsz),
		    "Memory not filled: nsz=%zu", nsz);
	}

	dallocx(p, 0);
}