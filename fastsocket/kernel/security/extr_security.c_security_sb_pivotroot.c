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
struct TYPE_2__ {int (* sb_pivotroot ) (struct path*,struct path*) ;} ;

/* Variables and functions */
 TYPE_1__* security_ops ; 
 int stub1 (struct path*,struct path*) ; 

int security_sb_pivotroot(struct path *old_path, struct path *new_path)
{
	return security_ops->sb_pivotroot(old_path, new_path);
}