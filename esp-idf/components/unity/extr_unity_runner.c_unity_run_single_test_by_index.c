#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ test_desc_t ;

/* Variables and functions */
 TYPE_1__* s_unity_tests_first ; 
 int /*<<< orphan*/  unity_run_single_test (TYPE_1__ const*) ; 

__attribute__((used)) static void unity_run_single_test_by_index(int index)
{
    const test_desc_t *test;
    for (test = s_unity_tests_first; test != NULL && index != 0; test = test->next, --index) {
        ;
    }
    if (test != NULL) {
        unity_run_single_test(test);
    }
}