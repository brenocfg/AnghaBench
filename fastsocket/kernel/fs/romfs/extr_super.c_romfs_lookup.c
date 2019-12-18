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
struct romfs_inode {int /*<<< orphan*/  spec; int /*<<< orphan*/  next; } ;
struct nameidata {int dummy; } ;
struct inode {unsigned long i_ino; int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {char* name; int len; } ;
struct dentry {TYPE_1__ d_name; } ;
typedef  int /*<<< orphan*/  ri ;

/* Variables and functions */
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 unsigned long ROMFH_HRD ; 
 unsigned long ROMFH_MASK ; 
 int ROMFH_SIZE ; 
 unsigned long ROMFH_TYPE ; 
 unsigned long be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 int romfs_dev_read (int /*<<< orphan*/ ,unsigned long,struct romfs_inode*,int) ; 
 int romfs_dev_strcmp (int /*<<< orphan*/ ,int,char const*,int) ; 
 struct inode* romfs_iget (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long romfs_maxsize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *romfs_lookup(struct inode *dir, struct dentry *dentry,
				   struct nameidata *nd)
{
	unsigned long offset, maxoff;
	struct inode *inode;
	struct romfs_inode ri;
	const char *name;		/* got from dentry */
	int len, ret;

	offset = dir->i_ino & ROMFH_MASK;
	ret = romfs_dev_read(dir->i_sb, offset, &ri, ROMFH_SIZE);
	if (ret < 0)
		goto error;

	/* search all the file entries in the list starting from the one
	 * pointed to by the directory's special data */
	maxoff = romfs_maxsize(dir->i_sb);
	offset = be32_to_cpu(ri.spec) & ROMFH_MASK;

	name = dentry->d_name.name;
	len = dentry->d_name.len;

	for (;;) {
		if (!offset || offset >= maxoff)
			goto out0;

		ret = romfs_dev_read(dir->i_sb, offset, &ri, sizeof(ri));
		if (ret < 0)
			goto error;

		/* try to match the first 16 bytes of name */
		ret = romfs_dev_strcmp(dir->i_sb, offset + ROMFH_SIZE, name,
				       len);
		if (ret < 0)
			goto error;
		if (ret == 1)
			break;

		/* next entry */
		offset = be32_to_cpu(ri.next) & ROMFH_MASK;
	}

	/* Hard link handling */
	if ((be32_to_cpu(ri.next) & ROMFH_TYPE) == ROMFH_HRD)
		offset = be32_to_cpu(ri.spec) & ROMFH_MASK;

	inode = romfs_iget(dir->i_sb, offset);
	if (IS_ERR(inode)) {
		ret = PTR_ERR(inode);
		goto error;
	}
	goto outi;

	/*
	 * it's a bit funky, _lookup needs to return an error code
	 * (negative) or a NULL, both as a dentry.  ENOENT should not
	 * be returned, instead we need to create a negative dentry by
	 * d_add(dentry, NULL); and return 0 as no error.
	 * (Although as I see, it only matters on writable file
	 * systems).
	 */
out0:
	inode = NULL;
outi:
	d_add(dentry, inode);
	ret = 0;
error:
	return ERR_PTR(ret);
}