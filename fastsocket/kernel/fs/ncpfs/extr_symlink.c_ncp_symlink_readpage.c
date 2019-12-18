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
struct page {TYPE_1__* mapping; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
typedef  scalar_t__ __le32 ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  file_handle; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NCPI_KLUDGE_SYMLINK ; 
 TYPE_2__* NCP_FINFO (struct inode*) ; 
 int NCP_MAX_SYMLINK_SIZE ; 
 int NCP_MIN_SYMLINK_SIZE ; 
 int /*<<< orphan*/  NCP_SERVER (struct inode*) ; 
 scalar_t__ NCP_SYMLINK_MAGIC0 ; 
 scalar_t__ NCP_SYMLINK_MAGIC1 ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  ncp_inode_close (struct inode*) ; 
 int /*<<< orphan*/  ncp_make_closed (struct inode*) ; 
 scalar_t__ ncp_make_open (struct inode*,int /*<<< orphan*/ ) ; 
 int ncp_read_kernel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int*) ; 
 int ncp_vol2io (int /*<<< orphan*/ ,char*,int*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int ncp_symlink_readpage(struct file *file, struct page *page)
{
	struct inode *inode = page->mapping->host;
	int error, length, len;
	char *link, *rawlink;
	char *buf = kmap(page);

	error = -ENOMEM;
	rawlink = kmalloc(NCP_MAX_SYMLINK_SIZE, GFP_KERNEL);
	if (!rawlink)
		goto fail;

	if (ncp_make_open(inode,O_RDONLY))
		goto failEIO;

	error=ncp_read_kernel(NCP_SERVER(inode),NCP_FINFO(inode)->file_handle,
                         0,NCP_MAX_SYMLINK_SIZE,rawlink,&length);

	ncp_inode_close(inode);
	/* Close file handle if no other users... */
	ncp_make_closed(inode);
	if (error)
		goto failEIO;

	if (NCP_FINFO(inode)->flags & NCPI_KLUDGE_SYMLINK) {
		if (length<NCP_MIN_SYMLINK_SIZE || 
		    ((__le32 *)rawlink)[0]!=NCP_SYMLINK_MAGIC0 ||
		    ((__le32 *)rawlink)[1]!=NCP_SYMLINK_MAGIC1)
		    	goto failEIO;
		link = rawlink + 8;
		length -= 8;
	} else {
		link = rawlink;
	}

	len = NCP_MAX_SYMLINK_SIZE;
	error = ncp_vol2io(NCP_SERVER(inode), buf, &len, link, length, 0);
	kfree(rawlink);
	if (error)
		goto fail;
	SetPageUptodate(page);
	kunmap(page);
	unlock_page(page);
	return 0;

failEIO:
	error = -EIO;
	kfree(rawlink);
fail:
	SetPageError(page);
	kunmap(page);
	unlock_page(page);
	return error;
}