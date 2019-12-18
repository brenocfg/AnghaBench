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
struct inode {int dummy; } ;
struct ctl_table_header {int dummy; } ;
struct TYPE_2__ {scalar_t__ sysctl; } ;

/* Variables and functions */
 TYPE_1__* PROC_I (struct inode*) ; 
 struct ctl_table_header* sysctl_head_grab (scalar_t__) ; 
 struct ctl_table_header* sysctl_head_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ctl_table_header *grab_header(struct inode *inode)
{
	if (PROC_I(inode)->sysctl)
		return sysctl_head_grab(PROC_I(inode)->sysctl);
	else
		return sysctl_head_next(NULL);
}