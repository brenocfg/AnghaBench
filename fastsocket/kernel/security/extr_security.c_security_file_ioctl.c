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
struct file {int dummy; } ;
struct TYPE_2__ {int (* file_ioctl ) (struct file*,unsigned int,unsigned long) ;} ;

/* Variables and functions */
 TYPE_1__* security_ops ; 
 int stub1 (struct file*,unsigned int,unsigned long) ; 

int security_file_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	return security_ops->file_ioctl(file, cmd, arg);
}