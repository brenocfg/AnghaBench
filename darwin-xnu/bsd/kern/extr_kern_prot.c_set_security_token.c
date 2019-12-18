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
typedef  TYPE_1__* proc_t ;
struct TYPE_4__ {int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int set_security_token_task_internal (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
set_security_token(proc_t p)
{
	return set_security_token_task_internal(p, p->task);
}