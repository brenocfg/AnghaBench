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
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EXT3_XATTR_INDEX_SECURITY ; 
 int ext3_xattr_set_handle (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ,char*,void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int security_inode_init_security (struct inode*,struct inode*,char**,void**,size_t*) ; 

int
ext3_init_security(handle_t *handle, struct inode *inode, struct inode *dir)
{
	int err;
	size_t len;
	void *value;
	char *name;

	err = security_inode_init_security(inode, dir, &name, &value, &len);
	if (err) {
		if (err == -EOPNOTSUPP)
			return 0;
		return err;
	}
	err = ext3_xattr_set_handle(handle, inode, EXT3_XATTR_INDEX_SECURITY,
				    name, value, len, 0);
	kfree(name);
	kfree(value);
	return err;
}