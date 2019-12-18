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
struct page {struct address_space* mapping; scalar_t__ index; } ;
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; } ;
struct cifs_sb_info {int dummy; } ;
struct cifsFileInfo {int /*<<< orphan*/  pid; } ;
struct address_space {struct inode* host; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_I (struct inode*) ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int EFAULT ; 
 int EIO ; 
 scalar_t__ PAGE_CACHE_SHIFT ; 
 unsigned int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  cFYI (int,char*) ; 
 int /*<<< orphan*/  cifsFileInfo_put (struct cifsFileInfo*) ; 
 int cifs_write (struct cifsFileInfo*,int /*<<< orphan*/ ,char*,unsigned int,scalar_t__*) ; 
 int /*<<< orphan*/  current_fs_time (int /*<<< orphan*/ ) ; 
 struct cifsFileInfo* find_writable_file (int /*<<< orphan*/ ,int) ; 
 char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 

__attribute__((used)) static int cifs_partialpagewrite(struct page *page, unsigned from, unsigned to)
{
	struct address_space *mapping = page->mapping;
	loff_t offset = (loff_t)page->index << PAGE_CACHE_SHIFT;
	char *write_data;
	int rc = -EFAULT;
	int bytes_written = 0;
	struct cifs_sb_info *cifs_sb;
	struct inode *inode;
	struct cifsFileInfo *open_file;

	if (!mapping || !mapping->host)
		return -EFAULT;

	inode = page->mapping->host;
	cifs_sb = CIFS_SB(inode->i_sb);

	offset += (loff_t)from;
	write_data = kmap(page);
	write_data += from;

	if ((to > PAGE_CACHE_SIZE) || (from > to)) {
		kunmap(page);
		return -EIO;
	}

	/* racing with truncate? */
	if (offset > mapping->host->i_size) {
		kunmap(page);
		return 0; /* don't care */
	}

	/* check to make sure that we are not extending the file */
	if (mapping->host->i_size - offset < (loff_t)to)
		to = (unsigned)(mapping->host->i_size - offset);

	open_file = find_writable_file(CIFS_I(mapping->host), false);
	if (open_file) {
		bytes_written = cifs_write(open_file, open_file->pid,
					   write_data, to - from, &offset);
		cifsFileInfo_put(open_file);
		/* Does mm or vfs already set times? */
		inode->i_atime = inode->i_mtime = current_fs_time(inode->i_sb);
		if ((bytes_written > 0) && (offset))
			rc = 0;
		else if (bytes_written < 0)
			rc = bytes_written;
	} else {
		cFYI(1, "No writeable filehandles for inode");
		rc = -EIO;
	}

	kunmap(page);
	return rc;
}