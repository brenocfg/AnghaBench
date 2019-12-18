#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct readdir_data {int used; void* dirent; scalar_t__ full; } ;
struct readdir_cd {scalar_t__ err; } ;
struct inode {int /*<<< orphan*/  i_mutex; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
struct buffered_dirent {scalar_t__ namlen; int /*<<< orphan*/  d_type; int /*<<< orphan*/  ino; int /*<<< orphan*/  offset; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  scalar_t__ (* filldir_t ) (struct readdir_cd*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  scalar_t__ __be32 ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 unsigned int ALIGN (scalar_t__,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nfs_ok ; 
 int /*<<< orphan*/  nfsd_buffered_filldir ; 
 scalar_t__ nfserr_eof ; 
 scalar_t__ nfserrno (int) ; 
 int /*<<< orphan*/  vfs_llseek (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vfs_readdir (struct file*,int /*<<< orphan*/ ,struct readdir_data*) ; 

__attribute__((used)) static __be32 nfsd_buffered_readdir(struct file *file, filldir_t func,
				    struct readdir_cd *cdp, loff_t *offsetp)
{
	struct readdir_data buf;
	struct buffered_dirent *de;
	int host_err;
	int size;
	loff_t offset;

	buf.dirent = (void *)__get_free_page(GFP_KERNEL);
	if (!buf.dirent)
		return nfserrno(-ENOMEM);

	offset = *offsetp;

	while (1) {
		struct inode *dir_inode = file->f_path.dentry->d_inode;
		unsigned int reclen;

		cdp->err = nfserr_eof; /* will be cleared on successful read */
		buf.used = 0;
		buf.full = 0;

		host_err = vfs_readdir(file, nfsd_buffered_filldir, &buf);
		if (buf.full)
			host_err = 0;

		if (host_err < 0)
			break;

		size = buf.used;

		if (!size)
			break;

		/*
		 * Various filldir functions may end up calling back into
		 * lookup_one_len() and the file system's ->lookup() method.
		 * These expect i_mutex to be held, as it would within readdir.
		 */
		host_err = mutex_lock_killable(&dir_inode->i_mutex);
		if (host_err)
			break;

		de = (struct buffered_dirent *)buf.dirent;
		while (size > 0) {
			offset = de->offset;

			if (func(cdp, de->name, de->namlen, de->offset,
				 de->ino, de->d_type))
				break;

			if (cdp->err != nfs_ok)
				break;

			reclen = ALIGN(sizeof(*de) + de->namlen,
				       sizeof(u64));
			size -= reclen;
			de = (struct buffered_dirent *)((char *)de + reclen);
		}
		mutex_unlock(&dir_inode->i_mutex);
		if (size > 0) /* We bailed out early */
			break;

		offset = vfs_llseek(file, 0, SEEK_CUR);
	}

	free_page((unsigned long)(buf.dirent));

	if (host_err)
		return nfserrno(host_err);

	*offsetp = offset;
	return cdp->err;
}