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
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int O_TRUNC ; 
 scalar_t__ special_file (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int open_will_truncate(int flag, struct inode *inode)
{
	/*
	 * We'll never write to the fs underlying
	 * a device file.
	 */
	if (special_file(inode->i_mode))
		return 0;
	return (flag & O_TRUNC);
}