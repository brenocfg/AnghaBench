#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tcase_test_function ;
struct TYPE_3__ {int allocated; int ntests; int /*<<< orphan*/ * tests; } ;
typedef  TYPE_1__ TCase ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,size_t) ; 

void
tcase_add_test(TCase *tc, tcase_test_function test)
{
    assert(tc != NULL);
    if (tc->allocated == tc->ntests) {
        int nalloc = tc->allocated + 100;
        size_t new_size = sizeof(tcase_test_function) * nalloc;
        tcase_test_function *new_tests = realloc(tc->tests, new_size);
        assert(new_tests != NULL);
        tc->tests = new_tests;
        tc->allocated = nalloc;
    }
    tc->tests[tc->ntests] = test;
    tc->ntests++;
}