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
struct hypfs_dbfs_file {int /*<<< orphan*/  data_free_work; int /*<<< orphan*/  lock; int /*<<< orphan*/  dentry; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data_free_delayed ; 
 int /*<<< orphan*/  dbfs_dir ; 
 int /*<<< orphan*/  dbfs_ops ; 
 int /*<<< orphan*/  debugfs_create_file (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct hypfs_dbfs_file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int hypfs_dbfs_create_file(struct hypfs_dbfs_file *df)
{
	df->dentry = debugfs_create_file(df->name, 0400, dbfs_dir, df,
					 &dbfs_ops);
	if (IS_ERR(df->dentry))
		return PTR_ERR(df->dentry);
	mutex_init(&df->lock);
	INIT_DELAYED_WORK(&df->data_free_work, data_free_delayed);
	return 0;
}