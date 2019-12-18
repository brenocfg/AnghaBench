#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; } ;
typedef  int __le32 ;
struct TYPE_9__ {int /*<<< orphan*/  file_handle; int /*<<< orphan*/  volNumber; } ;
struct TYPE_7__ {int flags; } ;
struct TYPE_8__ {TYPE_1__ m; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,struct inode*,struct dentry*,char const*) ; 
 int EIO ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_6__* NCP_FINFO (struct inode*) ; 
 unsigned int NCP_MAX_SYMLINK_SIZE ; 
 int NCP_MOUNT_SYMLINKS ; 
 TYPE_2__* NCP_SERVER (struct inode*) ; 
 int NCP_SYMLINK_MAGIC0 ; 
 int NCP_SYMLINK_MAGIC1 ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int S_IFLNK ; 
 int S_IRWXUGO ; 
 int aHIDDEN ; 
 int aSHARED ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ ncp_create_new (struct inode*,struct dentry*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ncp_inode_close (struct inode*) ; 
 int ncp_io2vol (TYPE_2__*,char*,int*,char const*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ncp_is_nfs_extras (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncp_make_closed (struct inode*) ; 
 scalar_t__ ncp_make_open (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ ncp_write_kernel (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int*) ; 
 int strlen (char const*) ; 

int ncp_symlink(struct inode *dir, struct dentry *dentry, const char *symname) {
	struct inode *inode;
	char *rawlink;
	int length, err, i, outlen;
	int kludge;
	int mode;
	__le32 attr;
	unsigned int hdr;

	DPRINTK("ncp_symlink(dir=%p,dentry=%p,symname=%s)\n",dir,dentry,symname);

	if (ncp_is_nfs_extras(NCP_SERVER(dir), NCP_FINFO(dir)->volNumber))
		kludge = 0;
	else
#ifdef CONFIG_NCPFS_EXTRAS
	if (NCP_SERVER(dir)->m.flags & NCP_MOUNT_SYMLINKS)
		kludge = 1;
	else
#endif
	/* EPERM is returned by VFS if symlink procedure does not exist */
		return -EPERM;
  
	rawlink = kmalloc(NCP_MAX_SYMLINK_SIZE, GFP_KERNEL);
	if (!rawlink)
		return -ENOMEM;

	if (kludge) {
		mode = 0;
		attr = aSHARED | aHIDDEN;
		((__le32 *)rawlink)[0]=NCP_SYMLINK_MAGIC0;
		((__le32 *)rawlink)[1]=NCP_SYMLINK_MAGIC1;
		hdr = 8;
	} else {
		mode = S_IFLNK | S_IRWXUGO;
		attr = 0;
		hdr = 0;
	}			

	length = strlen(symname);
	/* map to/from server charset, do not touch upper/lower case as
	   symlink can point out of ncp filesystem */
	outlen = NCP_MAX_SYMLINK_SIZE - hdr;
	err = ncp_io2vol(NCP_SERVER(dir), rawlink + hdr, &outlen, symname, length, 0);
	if (err)
		goto failfree;

	outlen += hdr;

	err = -EIO;
	if (ncp_create_new(dir,dentry,mode,0,attr)) {
		goto failfree;
	}

	inode=dentry->d_inode;

	if (ncp_make_open(inode, O_WRONLY))
		goto failfree;

	if (ncp_write_kernel(NCP_SERVER(inode), NCP_FINFO(inode)->file_handle, 
			     0, outlen, rawlink, &i) || i!=outlen) {
		goto fail;
	}

	ncp_inode_close(inode);
	ncp_make_closed(inode);
	kfree(rawlink);
	return 0;
fail:;
	ncp_inode_close(inode);
	ncp_make_closed(inode);
failfree:;
	kfree(rawlink);
	return err;
}