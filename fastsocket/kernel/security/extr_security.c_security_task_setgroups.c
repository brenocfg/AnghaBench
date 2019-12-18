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
struct group_info {int dummy; } ;
struct TYPE_2__ {int (* task_setgroups ) (struct group_info*) ;} ;

/* Variables and functions */
 TYPE_1__* security_ops ; 
 int stub1 (struct group_info*) ; 

int security_task_setgroups(struct group_info *group_info)
{
	return security_ops->task_setgroups(group_info);
}