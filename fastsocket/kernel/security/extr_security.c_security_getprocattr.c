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
struct task_struct {int dummy; } ;
struct TYPE_2__ {int (* getprocattr ) (struct task_struct*,char*,char**) ;} ;

/* Variables and functions */
 TYPE_1__* security_ops ; 
 int stub1 (struct task_struct*,char*,char**) ; 

int security_getprocattr(struct task_struct *p, char *name, char **value)
{
	return security_ops->getprocattr(p, name, value);
}