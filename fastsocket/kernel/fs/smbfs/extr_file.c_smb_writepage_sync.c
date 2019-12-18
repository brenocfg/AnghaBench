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
struct smb_sb_info {TYPE_1__* ops; } ;
struct page {scalar_t__ index; } ;
struct inode {unsigned long i_size; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ino; } ;
typedef  unsigned long loff_t ;
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  fileid; } ;
struct TYPE_3__ {int (* write ) (struct inode*,unsigned long,unsigned int,char*) ;} ;

/* Variables and functions */
 unsigned long PAGE_CACHE_SHIFT ; 
 int /*<<< orphan*/  PARANOIA (char*,unsigned int,int) ; 
 int /*<<< orphan*/  SMB_F_LOCALWRITE ; 
 TYPE_2__* SMB_I (struct inode*) ; 
 int /*<<< orphan*/  VERBOSE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  current_fs_time (int /*<<< orphan*/ ) ; 
 char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 struct smb_sb_info* server_from_inode (struct inode*) ; 
 unsigned int smb_get_wsize (struct smb_sb_info*) ; 
 int stub1 (struct inode*,unsigned long,unsigned int,char*) ; 

__attribute__((used)) static int
smb_writepage_sync(struct inode *inode, struct page *page,
		   unsigned long pageoffset, unsigned int count)
{
	loff_t offset;
	char *buffer = kmap(page) + pageoffset;
	struct smb_sb_info *server = server_from_inode(inode);
	unsigned int wsize = smb_get_wsize(server);
	int ret = 0;

	offset = ((loff_t)page->index << PAGE_CACHE_SHIFT) + pageoffset;
	VERBOSE("file ino=%ld, fileid=%d, count=%d@%Ld, wsize=%d\n",
		inode->i_ino, SMB_I(inode)->fileid, count, offset, wsize);

	do {
		int write_ret;

		if (count < wsize)
			wsize = count;

		write_ret = server->ops->write(inode, offset, wsize, buffer);
		if (write_ret < 0) {
			PARANOIA("failed write, wsize=%d, write_ret=%d\n",
				 wsize, write_ret);
			ret = write_ret;
			break;
		}
		/* N.B. what if result < wsize?? */
#ifdef SMBFS_PARANOIA
		if (write_ret < wsize)
			PARANOIA("short write, wsize=%d, write_ret=%d\n",
				 wsize, write_ret);
#endif
		buffer += wsize;
		offset += wsize;
		count -= wsize;
		/*
		 * Update the inode now rather than waiting for a refresh.
		 */
		inode->i_mtime = inode->i_atime = current_fs_time(inode->i_sb);
		SMB_I(inode)->flags |= SMB_F_LOCALWRITE;
		if (offset > inode->i_size)
			inode->i_size = offset;
	} while (count);

	kunmap(page);
	return ret;
}