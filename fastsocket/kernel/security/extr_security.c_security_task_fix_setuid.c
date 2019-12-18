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
struct cred {int dummy; } ;
struct TYPE_2__ {int (* task_fix_setuid ) (struct cred*,struct cred const*,int) ;} ;

/* Variables and functions */
 TYPE_1__* security_ops ; 
 int stub1 (struct cred*,struct cred const*,int) ; 

int security_task_fix_setuid(struct cred *new, const struct cred *old,
			     int flags)
{
	return security_ops->task_fix_setuid(new, old, flags);
}