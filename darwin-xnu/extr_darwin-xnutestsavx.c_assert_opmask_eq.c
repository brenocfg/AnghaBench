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
typedef  scalar_t__ OPMASK ;

/* Variables and functions */
 int KARRAY_MAX ; 
 int /*<<< orphan*/  T_ASSERT_FAIL (char*) ; 
 int /*<<< orphan*/  T_LOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  karray_str_buf ; 
 int /*<<< orphan*/  opmask_to_string (scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
assert_opmask_eq(OPMASK *a, OPMASK *b) {
	for (int i = 0; i < KARRAY_MAX; i++) {
		if (a[i] != b[i]) {
			opmask_to_string(a, karray_str_buf);
			T_LOG("Compare failed, opmask A:\n%s", karray_str_buf);
			opmask_to_string(b, karray_str_buf);
			T_LOG("Compare failed, opmask B:\n%s", karray_str_buf);
			T_ASSERT_FAIL("opmasks not equal");
		}
	}
}