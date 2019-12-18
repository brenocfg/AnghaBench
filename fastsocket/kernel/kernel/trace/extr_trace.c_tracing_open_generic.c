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
struct inode {int /*<<< orphan*/  i_private; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ tracing_disabled ; 

int tracing_open_generic(struct inode *inode, struct file *filp)
{
	if (tracing_disabled)
		return -ENODEV;

	filp->private_data = inode->i_private;
	return 0;
}