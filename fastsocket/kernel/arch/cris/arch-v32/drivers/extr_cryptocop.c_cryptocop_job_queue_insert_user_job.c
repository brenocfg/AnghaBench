#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cryptocop_operation {int dummy; } ;

/* Variables and functions */
 int cryptocop_job_queue_insert (int /*<<< orphan*/ ,struct cryptocop_operation*) ; 
 int /*<<< orphan*/  cryptocop_prio_user ; 

int cryptocop_job_queue_insert_user_job(struct cryptocop_operation *operation)
{
	return cryptocop_job_queue_insert(cryptocop_prio_user, operation);
}