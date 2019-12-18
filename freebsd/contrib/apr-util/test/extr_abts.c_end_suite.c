#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ failed; int num_test; } ;
typedef  TYPE_1__ sub_suite ;
struct TYPE_5__ {TYPE_1__* tail; } ;
typedef  TYPE_2__ abts_suite ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  quiet ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void end_suite(abts_suite *suite)
{
    if (suite != NULL) {
        sub_suite *last = suite->tail;
        if (!quiet) {
            fprintf(stdout, "\b");
            fflush(stdout);
        }
        if (last->failed == 0) {
            fprintf(stdout, "SUCCESS\n");
            fflush(stdout);
        }
        else {
            fprintf(stdout, "FAILED %d of %d\n", last->failed, last->num_test);
            fflush(stdout);
        }
    }
}