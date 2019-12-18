#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct proc_dir_entry {scalar_t__ data; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct proc_dir_entry* PDE (struct inode*) ; 

__attribute__((used)) static int scanlog_release(struct inode * inode, struct file * file)
{
	struct proc_dir_entry *dp = PDE(inode);
	unsigned int *data = (unsigned int *)dp->data;

	data[0] = 0;

	return 0;
}