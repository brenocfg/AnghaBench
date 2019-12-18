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
struct TYPE_2__ {int /*<<< orphan*/  generic_ip; } ;
struct inode {TYPE_1__ u; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */

__attribute__((used)) static int open_file_generic(struct inode *inode, struct file *file)
{
	file->private_data = inode->u.generic_ip;
	return 0;
}