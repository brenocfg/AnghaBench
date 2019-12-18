#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sysfs_inode_attrs {int /*<<< orphan*/  ia_secdata_len; scalar_t__ ia_secdata; int /*<<< orphan*/  ia_iattr; } ;
struct TYPE_6__ {struct bin_attribute* bin_attr; } ;
struct TYPE_5__ {int /*<<< orphan*/  subdirs; } ;
struct sysfs_dirent {TYPE_3__ s_bin_attr; TYPE_2__ s_dir; int /*<<< orphan*/  s_mode; struct sysfs_inode_attrs* s_iattr; int /*<<< orphan*/  s_ino; } ;
struct inode {int /*<<< orphan*/ * i_op; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_ino; TYPE_1__* i_mapping; int /*<<< orphan*/  i_private; } ;
struct bin_attribute {int /*<<< orphan*/  size; } ;
struct TYPE_4__ {int /*<<< orphan*/ * backing_dev_info; int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
#define  SYSFS_DIR 131 
#define  SYSFS_KOBJ_ATTR 130 
#define  SYSFS_KOBJ_BIN_ATTR 129 
#define  SYSFS_KOBJ_LINK 128 
 int /*<<< orphan*/  bin_fops ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  security_inode_notifysecctx (struct inode*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_default_inode_attr (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_inode_attr (struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_aops ; 
 int /*<<< orphan*/  sysfs_backing_dev_info ; 
 int /*<<< orphan*/  sysfs_dir_inode_operations ; 
 int /*<<< orphan*/  sysfs_dir_operations ; 
 int /*<<< orphan*/  sysfs_file_operations ; 
 int /*<<< orphan*/  sysfs_get (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  sysfs_inode_imutex_key ; 
 int /*<<< orphan*/  sysfs_inode_operations ; 
 int /*<<< orphan*/  sysfs_symlink_inode_operations ; 
 int sysfs_type (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

__attribute__((used)) static void sysfs_init_inode(struct sysfs_dirent *sd, struct inode *inode)
{
	struct bin_attribute *bin_attr;
	struct sysfs_inode_attrs *iattrs;

	inode->i_private = sysfs_get(sd);
	inode->i_mapping->a_ops = &sysfs_aops;
	inode->i_mapping->backing_dev_info = &sysfs_backing_dev_info;
	inode->i_op = &sysfs_inode_operations;
	inode->i_ino = sd->s_ino;
	lockdep_set_class(&inode->i_mutex, &sysfs_inode_imutex_key);

	iattrs = sd->s_iattr;
	if (iattrs) {
		/* sysfs_dirent has non-default attributes
		 * get them for the new inode from persistent copy
		 * in sysfs_dirent
		 */
		set_inode_attr(inode, &iattrs->ia_iattr);
		if (iattrs->ia_secdata)
			security_inode_notifysecctx(inode,
						iattrs->ia_secdata,
						iattrs->ia_secdata_len);
	} else
		set_default_inode_attr(inode, sd->s_mode);

	/* initialize inode according to type */
	switch (sysfs_type(sd)) {
	case SYSFS_DIR:
		inode->i_op = &sysfs_dir_inode_operations;
		inode->i_fop = &sysfs_dir_operations;
		inode->i_nlink = sd->s_dir.subdirs + 2;
		break;
	case SYSFS_KOBJ_ATTR:
		inode->i_size = PAGE_SIZE;
		inode->i_fop = &sysfs_file_operations;
		break;
	case SYSFS_KOBJ_BIN_ATTR:
		bin_attr = sd->s_bin_attr.bin_attr;
		inode->i_size = bin_attr->size;
		inode->i_fop = &bin_fops;
		break;
	case SYSFS_KOBJ_LINK:
		inode->i_op = &sysfs_symlink_inode_operations;
		break;
	default:
		BUG();
	}

	unlock_new_inode(inode);
}