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
struct file {void* private_data; } ;
struct TYPE_2__ {scalar_t__ self_exec_id; } ;

/* Variables and functions */
 TYPE_1__* current ; 

__attribute__((used)) static int mem_open(struct inode* inode, struct file* file)
{
	file->private_data = (void*)((long)current->self_exec_id);
	return 0;
}