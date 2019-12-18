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
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 struct dentry* debugfs_create_file (char const*,int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fops_bool ; 

struct dentry *debugfs_create_bool(const char *name, mode_t mode,
				   struct dentry *parent, u32 *value)
{
	return debugfs_create_file(name, mode, parent, value, &fops_bool);
}