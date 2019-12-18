#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int umode_t ;
struct nw_modify_dos_info {int attributes; int /*<<< orphan*/  lastAccessDate; int /*<<< orphan*/  modifyDate; int /*<<< orphan*/  modifyTime; int /*<<< orphan*/  creationDate; int /*<<< orphan*/  creationTime; } ;
struct TYPE_6__ {scalar_t__ uid; scalar_t__ gid; int dir_mode; int flags; int file_mode; } ;
struct ncp_server {TYPE_1__ m; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct TYPE_9__ {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_8__ {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_7__ {int /*<<< orphan*/  tv_sec; } ;
struct iattr {int ia_valid; scalar_t__ ia_uid; scalar_t__ ia_gid; int ia_mode; TYPE_4__ ia_atime; TYPE_3__ ia_mtime; TYPE_2__ ia_ctime; int /*<<< orphan*/  ia_size; } ;
struct dentry {struct inode* d_inode; } ;
typedef  int /*<<< orphan*/  info ;
typedef  int __le32 ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_10__ {int nwattr; int /*<<< orphan*/  file_handle; int /*<<< orphan*/  dirEntNum; int /*<<< orphan*/  volNumber; } ;

/* Variables and functions */
 int ATTR_ATIME ; 
 int ATTR_CTIME ; 
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_MTIME ; 
 int ATTR_SIZE ; 
 int ATTR_UID ; 
 int DM_ATTRIBUTES ; 
 int DM_CREATE_DATE ; 
 int DM_CREATE_TIME ; 
 int DM_LAST_ACCESS_DATE ; 
 int DM_MODIFY_DATE ; 
 int DM_MODIFY_TIME ; 
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ) ; 
 int EACCES ; 
 int EIO ; 
 int EPERM ; 
 TYPE_5__* NCP_FINFO (struct inode*) ; 
 int NCP_MOUNT_EXTRAS ; 
 struct ncp_server* NCP_SERVER (struct inode*) ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int S_IFDIR ; 
 int S_IFREG ; 
 int S_IRUGO ; 
 int S_IRWXUGO ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int S_IWUGO ; 
 int S_IXUGO ; 
 int aDELETEINHIBIT ; 
 int aRENAMEINHIBIT ; 
 int aRONLY ; 
 int aSHARED ; 
 int aSYSTEM ; 
 int inode_change_ok (struct inode*,struct iattr*) ; 
 int inode_setattr (struct inode*,struct iattr*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  memset (struct nw_modify_dos_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ncp_age_dentry (struct ncp_server*,struct dentry*) ; 
 int /*<<< orphan*/  ncp_conn_valid (struct ncp_server*) ; 
 int /*<<< orphan*/  ncp_date_unix2dos (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncp_inode_close (struct inode*) ; 
 scalar_t__ ncp_is_nfs_extras (struct ncp_server*,int /*<<< orphan*/ ) ; 
 int ncp_make_closed (struct inode*) ; 
 int ncp_make_open (struct inode*,int /*<<< orphan*/ ) ; 
 int ncp_modify_file_or_subdir_dos_info (struct ncp_server*,struct inode*,int,struct nw_modify_dos_info*) ; 
 int ncp_modify_nfs_info (struct ncp_server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncp_write_kernel (struct ncp_server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

int ncp_notify_change(struct dentry *dentry, struct iattr *attr)
{
	struct inode *inode = dentry->d_inode;
	int result = 0;
	__le32 info_mask;
	struct nw_modify_dos_info info;
	struct ncp_server *server;

	result = -EIO;

	lock_kernel();	

	server = NCP_SERVER(inode);
	if ((!server) || !ncp_conn_valid(server))
		goto out;

	/* ageing the dentry to force validation */
	ncp_age_dentry(server, dentry);

	result = inode_change_ok(inode, attr);
	if (result < 0)
		goto out;

	result = -EPERM;
	if (((attr->ia_valid & ATTR_UID) &&
	     (attr->ia_uid != server->m.uid)))
		goto out;

	if (((attr->ia_valid & ATTR_GID) &&
	     (attr->ia_gid != server->m.gid)))
		goto out;

	if (((attr->ia_valid & ATTR_MODE) &&
	     (attr->ia_mode &
	      ~(S_IFREG | S_IFDIR | S_IRWXUGO))))
		goto out;

	info_mask = 0;
	memset(&info, 0, sizeof(info));

#if 1 
        if ((attr->ia_valid & ATTR_MODE) != 0)
        {
		umode_t newmode = attr->ia_mode;

		info_mask |= DM_ATTRIBUTES;

                if (S_ISDIR(inode->i_mode)) {
                	newmode &= server->m.dir_mode;
		} else {
#ifdef CONFIG_NCPFS_EXTRAS			
			if (server->m.flags & NCP_MOUNT_EXTRAS) {
				/* any non-default execute bit set */
				if (newmode & ~server->m.file_mode & S_IXUGO)
					info.attributes |= aSHARED | aSYSTEM;
				/* read for group/world and not in default file_mode */
				else if (newmode & ~server->m.file_mode & S_IRUGO)
					info.attributes |= aSHARED;
			} else
#endif
				newmode &= server->m.file_mode;			
                }
                if (newmode & S_IWUGO)
                	info.attributes &= ~(aRONLY|aRENAMEINHIBIT|aDELETEINHIBIT);
                else
			info.attributes |=  (aRONLY|aRENAMEINHIBIT|aDELETEINHIBIT);

#ifdef CONFIG_NCPFS_NFS_NS
		if (ncp_is_nfs_extras(server, NCP_FINFO(inode)->volNumber)) {
			result = ncp_modify_nfs_info(server,
						     NCP_FINFO(inode)->volNumber,
						     NCP_FINFO(inode)->dirEntNum,
						     attr->ia_mode, 0);
			if (result != 0)
				goto out;
			info.attributes &= ~(aSHARED | aSYSTEM);
			{
				/* mark partial success */
				struct iattr tmpattr;
				
				tmpattr.ia_valid = ATTR_MODE;
				tmpattr.ia_mode = attr->ia_mode;

				result = inode_setattr(inode, &tmpattr);
				if (result)
					goto out;
			}
		}
#endif
        }
#endif

	/* Do SIZE before attributes, otherwise mtime together with size does not work...
	 */
	if ((attr->ia_valid & ATTR_SIZE) != 0) {
		int written;

		DPRINTK("ncpfs: trying to change size to %ld\n",
			attr->ia_size);

		if ((result = ncp_make_open(inode, O_WRONLY)) < 0) {
			result = -EACCES;
			goto out;
		}
		ncp_write_kernel(NCP_SERVER(inode), NCP_FINFO(inode)->file_handle,
			  attr->ia_size, 0, "", &written);

		/* According to ndir, the changes only take effect after
		   closing the file */
		ncp_inode_close(inode);
		result = ncp_make_closed(inode);
		if (result)
			goto out;
		{
			struct iattr tmpattr;
			
			tmpattr.ia_valid = ATTR_SIZE;
			tmpattr.ia_size = attr->ia_size;
			
			result = inode_setattr(inode, &tmpattr);
			if (result)
				goto out;
		}
	}
	if ((attr->ia_valid & ATTR_CTIME) != 0) {
		info_mask |= (DM_CREATE_TIME | DM_CREATE_DATE);
		ncp_date_unix2dos(attr->ia_ctime.tv_sec,
			     &info.creationTime, &info.creationDate);
	}
	if ((attr->ia_valid & ATTR_MTIME) != 0) {
		info_mask |= (DM_MODIFY_TIME | DM_MODIFY_DATE);
		ncp_date_unix2dos(attr->ia_mtime.tv_sec,
				  &info.modifyTime, &info.modifyDate);
	}
	if ((attr->ia_valid & ATTR_ATIME) != 0) {
		__le16 dummy;
		info_mask |= (DM_LAST_ACCESS_DATE);
		ncp_date_unix2dos(attr->ia_atime.tv_sec,
				  &dummy, &info.lastAccessDate);
	}
	if (info_mask != 0) {
		result = ncp_modify_file_or_subdir_dos_info(NCP_SERVER(inode),
				      inode, info_mask, &info);
		if (result != 0) {
			result = -EACCES;

			if (info_mask == (DM_CREATE_TIME | DM_CREATE_DATE)) {
				/* NetWare seems not to allow this. I
				   do not know why. So, just tell the
				   user everything went fine. This is
				   a terrible hack, but I do not know
				   how to do this correctly. */
				result = 0;
			} else
				goto out;
		}
#ifdef CONFIG_NCPFS_STRONG		
		if ((!result) && (info_mask & DM_ATTRIBUTES))
			NCP_FINFO(inode)->nwattr = info.attributes;
#endif
	}
	if (!result)
		result = inode_setattr(inode, attr);
out:
	unlock_kernel();
	return result;
}