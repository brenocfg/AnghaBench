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
struct dentry {int /*<<< orphan*/ * d_op; int /*<<< orphan*/  d_fsdata; } ;
struct configfs_dirent {struct dentry* s_dentry; struct configfs_attribute* s_element; } ;
struct configfs_attribute {int ca_mode; } ;

/* Variables and functions */
 int S_IALLUGO ; 
 int S_IFREG ; 
 int configfs_create (struct dentry*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configfs_dentry_ops ; 
 int /*<<< orphan*/  configfs_get (struct configfs_dirent*) ; 
 int /*<<< orphan*/  configfs_init_file ; 
 int /*<<< orphan*/  configfs_put (struct configfs_dirent*) ; 
 int /*<<< orphan*/  d_rehash (struct dentry*) ; 

__attribute__((used)) static int configfs_attach_attr(struct configfs_dirent * sd, struct dentry * dentry)
{
	struct configfs_attribute * attr = sd->s_element;
	int error;

	dentry->d_fsdata = configfs_get(sd);
	sd->s_dentry = dentry;
	error = configfs_create(dentry, (attr->ca_mode & S_IALLUGO) | S_IFREG,
				configfs_init_file);
	if (error) {
		configfs_put(sd);
		return error;
	}

	dentry->d_op = &configfs_dentry_ops;
	d_rehash(dentry);

	return 0;
}