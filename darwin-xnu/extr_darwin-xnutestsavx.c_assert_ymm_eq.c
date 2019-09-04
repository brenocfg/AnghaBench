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
 int /*<<< orphan*/  T_ASSERT_FAIL (char*) ; 
 int /*<<< orphan*/  T_LOG (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp_unoptimized (void*,void*,int) ; 
 int /*<<< orphan*/  vec256_to_string (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec_str_buf ; 

void
assert_ymm_eq(void *a, void *b, int c) {
	if(memcmp_unoptimized(a, b, c)) {
		vec256_to_string(a, vec_str_buf);
		T_LOG("Compare failed, vector A:\n%s", vec_str_buf);
		vec256_to_string(b, vec_str_buf);
		T_LOG("Compare failed, vector B:\n%s", vec_str_buf);
		T_ASSERT_FAIL("vectors not equal");
	}
}