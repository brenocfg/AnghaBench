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
typedef  int /*<<< orphan*/  u32 ;
struct cred {int dummy; } ;
struct TYPE_2__ {int (* kernel_act_as ) (struct cred*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* security_ops ; 
 int stub1 (struct cred*,int /*<<< orphan*/ ) ; 

int security_kernel_act_as(struct cred *new, u32 secid)
{
	return security_ops->kernel_act_as(new, secid);
}