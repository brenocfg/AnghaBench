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
struct dentry {int /*<<< orphan*/  d_inode; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t ERANGE ; 
 int /*<<< orphan*/  NFS_SERVER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XATTR_NAME_NFSV4_ACL ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  nfs4_server_supports_acls (int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

ssize_t nfs4_listxattr(struct dentry *dentry, char *buf, size_t buflen)
{
	size_t len = strlen(XATTR_NAME_NFSV4_ACL) + 1;

	if (!nfs4_server_supports_acls(NFS_SERVER(dentry->d_inode)))
		return 0;
	if (buf && buflen < len)
		return -ERANGE;
	if (buf)
		memcpy(buf, XATTR_NAME_NFSV4_ACL, len);
	return len;
}