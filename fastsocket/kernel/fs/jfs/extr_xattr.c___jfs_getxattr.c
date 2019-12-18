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
struct jfs_ea_list {int dummy; } ;
struct jfs_ea {int namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  valuelen; } ;
struct inode {int dummy; } ;
struct ea_buffer {scalar_t__ xattr; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  xattr_sem; } ;

/* Variables and functions */
 struct jfs_ea* END_EALIST (struct jfs_ea_list*) ; 
 size_t ENODATA ; 
 size_t ENOMEM ; 
 size_t ERANGE ; 
 struct jfs_ea* FIRST_EA (struct jfs_ea_list*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* JFS_IP (struct inode*) ; 
 struct jfs_ea* NEXT_EA (struct jfs_ea*) ; 
 int /*<<< orphan*/  XATTR_OS2_PREFIX ; 
 int XATTR_OS2_PREFIX_LEN ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int ea_get (struct inode*,struct ea_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ea_release (struct inode*,struct ea_buffer*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (void*,char*,size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

ssize_t __jfs_getxattr(struct inode *inode, const char *name, void *data,
		       size_t buf_size)
{
	struct jfs_ea_list *ealist;
	struct jfs_ea *ea;
	struct ea_buffer ea_buf;
	int xattr_size;
	ssize_t size;
	int namelen = strlen(name);
	char *os2name = NULL;
	char *value;

	if (strncmp(name, XATTR_OS2_PREFIX, XATTR_OS2_PREFIX_LEN) == 0) {
		os2name = kmalloc(namelen - XATTR_OS2_PREFIX_LEN + 1,
				  GFP_KERNEL);
		if (!os2name)
			return -ENOMEM;
		strcpy(os2name, name + XATTR_OS2_PREFIX_LEN);
		name = os2name;
		namelen -= XATTR_OS2_PREFIX_LEN;
	}

	down_read(&JFS_IP(inode)->xattr_sem);

	xattr_size = ea_get(inode, &ea_buf, 0);

	if (xattr_size < 0) {
		size = xattr_size;
		goto out;
	}

	if (xattr_size == 0)
		goto not_found;

	ealist = (struct jfs_ea_list *) ea_buf.xattr;

	/* Find the named attribute */
	for (ea = FIRST_EA(ealist); ea < END_EALIST(ealist); ea = NEXT_EA(ea))
		if ((namelen == ea->namelen) &&
		    memcmp(name, ea->name, namelen) == 0) {
			/* Found it */
			size = le16_to_cpu(ea->valuelen);
			if (!data)
				goto release;
			else if (size > buf_size) {
				size = -ERANGE;
				goto release;
			}
			value = ((char *) &ea->name) + ea->namelen + 1;
			memcpy(data, value, size);
			goto release;
		}
      not_found:
	size = -ENODATA;
      release:
	ea_release(inode, &ea_buf);
      out:
	up_read(&JFS_IP(inode)->xattr_sem);

	kfree(os2name);

	return size;
}