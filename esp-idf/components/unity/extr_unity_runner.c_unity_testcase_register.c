#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ test_desc_t ;

/* Variables and functions */
 TYPE_1__* s_unity_tests_first ; 
 TYPE_1__* s_unity_tests_last ; 

void unity_testcase_register(test_desc_t *desc)
{
    if (!s_unity_tests_first) {
        s_unity_tests_first = desc;
        s_unity_tests_last = desc;
    } else {
        test_desc_t *temp = s_unity_tests_first;
        s_unity_tests_first = desc;
        s_unity_tests_first->next = temp;
    }
}