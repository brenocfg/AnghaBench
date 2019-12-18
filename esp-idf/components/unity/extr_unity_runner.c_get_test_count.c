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
struct TYPE_3__ {struct TYPE_3__* next; } ;
typedef  TYPE_1__ test_desc_t ;

/* Variables and functions */
 TYPE_1__* s_unity_tests_first ; 

__attribute__((used)) static int get_test_count(void)
{
    int test_counter = 0;
    for (const test_desc_t *test = s_unity_tests_first;
            test != NULL;
            test = test->next) {
        ++test_counter;
    }
    return test_counter;
}