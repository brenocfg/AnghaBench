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
struct TYPE_4__ {int /*<<< orphan*/ * suite; } ;
typedef  int /*<<< orphan*/  Suite ;
typedef  TYPE_1__ SRunner ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 

SRunner *
srunner_create(Suite *suite)
{
    SRunner *runner = calloc(1, sizeof(SRunner));
    if (runner != NULL) {
        runner->suite = suite;
    }
    return runner;
}