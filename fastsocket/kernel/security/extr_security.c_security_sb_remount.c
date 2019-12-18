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
struct super_block {int dummy; } ;
struct TYPE_2__ {int (* sb_remount ) (struct super_block*,void*) ;} ;

/* Variables and functions */
 TYPE_1__* security_ops ; 
 int stub1 (struct super_block*,void*) ; 

int security_sb_remount(struct super_block *sb, void *data)
{
	return security_ops->sb_remount(sb, data);
}