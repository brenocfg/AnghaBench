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
typedef  int /*<<< orphan*/  u32 ;
struct dentry {int dummy; } ;
typedef  int mode_t ;

/* Variables and functions */
 int S_IRUGO ; 
 int S_IWUGO ; 
 struct dentry* debugfs_create_file (char const*,int,struct dentry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fops_x32 ; 
 int /*<<< orphan*/  fops_x32_ro ; 
 int /*<<< orphan*/  fops_x32_wo ; 

struct dentry *debugfs_create_x32(const char *name, mode_t mode,
				 struct dentry *parent, u32 *value)
{
	/* if there are no write bits set, make read only */
	if (!(mode & S_IWUGO))
		return debugfs_create_file(name, mode, parent, value, &fops_x32_ro);
	/* if there are no read bits set, make write only */
	if (!(mode & S_IRUGO))
		return debugfs_create_file(name, mode, parent, value, &fops_x32_wo);

	return debugfs_create_file(name, mode, parent, value, &fops_x32);
}