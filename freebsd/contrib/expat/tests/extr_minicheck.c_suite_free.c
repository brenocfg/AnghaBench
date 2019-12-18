#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* tests; } ;
struct TYPE_6__ {struct TYPE_6__* next_tcase; } ;
typedef  TYPE_1__ TCase ;
typedef  TYPE_2__ Suite ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  tcase_free (TYPE_1__*) ; 

__attribute__((used)) static void
suite_free(Suite *suite)
{
    if (! suite) {
        return;
    }

    while (suite->tests != NULL) {
        TCase *next = suite->tests->next_tcase;
        tcase_free(suite->tests);
        suite->tests = next;
    }
    free(suite);
}