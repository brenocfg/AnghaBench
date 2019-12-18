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
struct TYPE_2__ {int (* task_create ) (unsigned long) ;} ;

/* Variables and functions */
 TYPE_1__* security_ops ; 
 int stub1 (unsigned long) ; 

int security_task_create(unsigned long clone_flags)
{
	return security_ops->task_create(clone_flags);
}