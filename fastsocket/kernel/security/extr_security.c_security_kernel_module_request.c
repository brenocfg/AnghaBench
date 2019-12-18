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
struct TYPE_2__ {int (* kernel_module_request ) (char*) ;} ;

/* Variables and functions */
 TYPE_1__* security_ops ; 
 int stub1 (char*) ; 

int security_kernel_module_request(char *kmod_name)
{
	return security_ops->kernel_module_request(kmod_name);
}