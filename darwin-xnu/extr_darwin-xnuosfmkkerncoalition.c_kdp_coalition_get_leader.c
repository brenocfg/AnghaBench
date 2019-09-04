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
typedef  int /*<<< orphan*/  task_t ;
typedef  TYPE_2__* coalition_t ;
struct TYPE_4__ {int /*<<< orphan*/  leader; } ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ j; } ;

/* Variables and functions */
 scalar_t__ COALITION_TYPE_JETSAM ; 
 int /*<<< orphan*/  TASK_NULL ; 

task_t kdp_coalition_get_leader(coalition_t coal)
{
	if (!coal)
		return TASK_NULL;

	if (coal->type == COALITION_TYPE_JETSAM) {
		return coal->j.leader;
	}
	return TASK_NULL;
}