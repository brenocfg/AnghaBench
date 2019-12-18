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
struct dentry {TYPE_2__* d_inode; } ;
typedef  int loff_t ;
struct TYPE_4__ {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_atime; } ;
struct TYPE_3__ {int (* read ) (TYPE_2__*,int,unsigned int,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DENTRY_PATH (struct dentry*) ; 
 int PAGE_CACHE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SMB_O_RDONLY ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  VERBOSE (char*,int /*<<< orphan*/ ,int,int,unsigned int) ; 
 int /*<<< orphan*/  current_fs_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 struct smb_sb_info* server_from_dentry (struct dentry*) ; 
 unsigned int smb_get_rsize (struct smb_sb_info*) ; 
 int smb_open (struct dentry*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,int,unsigned int,char*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int
smb_readpage_sync(struct dentry *dentry, struct page *page)
{
	char *buffer = kmap(page);
	loff_t offset = (loff_t)page->index << PAGE_CACHE_SHIFT;
	struct smb_sb_info *server = server_from_dentry(dentry);
	unsigned int rsize = smb_get_rsize(server);
	int count = PAGE_SIZE;
	int result;

	VERBOSE("file %s/%s, count=%d@%Ld, rsize=%d\n",
		DENTRY_PATH(dentry), count, offset, rsize);

	result = smb_open(dentry, SMB_O_RDONLY);
	if (result < 0)
		goto io_error;

	do {
		if (count < rsize)
			rsize = count;

		result = server->ops->read(dentry->d_inode,offset,rsize,buffer);
		if (result < 0)
			goto io_error;

		count -= result;
		offset += result;
		buffer += result;
		dentry->d_inode->i_atime =
			current_fs_time(dentry->d_inode->i_sb);
		if (result < rsize)
			break;
	} while (count);

	memset(buffer, 0, count);
	flush_dcache_page(page);
	SetPageUptodate(page);
	result = 0;

io_error:
	kunmap(page);
	unlock_page(page);
	return result;
}