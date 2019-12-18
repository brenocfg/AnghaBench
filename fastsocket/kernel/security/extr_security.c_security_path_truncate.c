#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct path {TYPE_1__* dentry; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_4__ {int (* path_truncate ) (struct path*,int /*<<< orphan*/ ,unsigned int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_PRIVATE (int /*<<< orphan*/ ) ; 
 TYPE_2__* security_ops ; 
 int stub1 (struct path*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int security_path_truncate(struct path *path, loff_t length,
			   unsigned int time_attrs)
{
	if (unlikely(IS_PRIVATE(path->dentry->d_inode)))
		return 0;
	return security_ops->path_truncate(path, length, time_attrs);
}