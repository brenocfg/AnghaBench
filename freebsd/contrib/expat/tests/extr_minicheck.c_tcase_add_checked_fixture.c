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
typedef  int /*<<< orphan*/  tcase_teardown_function ;
typedef  int /*<<< orphan*/  tcase_setup_function ;
struct TYPE_3__ {int /*<<< orphan*/  teardown; int /*<<< orphan*/  setup; } ;
typedef  TYPE_1__ TCase ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void
tcase_add_checked_fixture(TCase *tc,
                          tcase_setup_function setup,
                          tcase_teardown_function teardown)
{
    assert(tc != NULL);
    tc->setup = setup;
    tc->teardown = teardown;
}