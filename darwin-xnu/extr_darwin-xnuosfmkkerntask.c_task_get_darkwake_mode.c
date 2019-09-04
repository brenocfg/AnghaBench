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
typedef  TYPE_1__* task_t ;
typedef  int boolean_t ;
struct TYPE_4__ {int t_flags; } ;

/* Variables and functions */
 int TF_DARKWAKE_MODE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

boolean_t
task_get_darkwake_mode(task_t task)
{
	assert(task);
	return ((task->t_flags & TF_DARKWAKE_MODE) != 0);
}