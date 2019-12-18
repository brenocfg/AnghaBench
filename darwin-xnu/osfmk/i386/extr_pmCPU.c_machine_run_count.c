#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* pmSetRunCount ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* pmDispatch ; 
 int /*<<< orphan*/  saved_run_count ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void
machine_run_count(uint32_t count)
{
    if (pmDispatch != NULL
	&& pmDispatch->pmSetRunCount != NULL)
	pmDispatch->pmSetRunCount(count);
    else
	saved_run_count = count;
}