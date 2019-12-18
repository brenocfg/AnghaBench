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
struct path {int dummy; } ;
struct TYPE_2__ {int (* sb_mount ) (char*,struct path*,char*,unsigned long,void*) ;} ;

/* Variables and functions */
 TYPE_1__* security_ops ; 
 int stub1 (char*,struct path*,char*,unsigned long,void*) ; 

int security_sb_mount(char *dev_name, struct path *path,
                       char *type, unsigned long flags, void *data)
{
	return security_ops->sb_mount(dev_name, path, type, flags, data);
}