#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct page {TYPE_1__* mapping; } ;
struct nfs_open_context {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_12__ {TYPE_5__* dentry; } ;
struct file {TYPE_6__ f_path; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
struct TYPE_11__ {TYPE_4__ d_name; TYPE_3__* d_parent; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {TYPE_2__ d_name; } ;
struct TYPE_7__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSIOS_VFSUPDATEPAGE ; 
 int /*<<< orphan*/  dprintk (char*,int,long long,...) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 unsigned int max (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_can_extend_write (struct file*,struct page*,struct inode*) ; 
 struct nfs_open_context* nfs_file_open_context (struct file*) ; 
 int /*<<< orphan*/  nfs_inc_stats (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_page_length (struct page*) ; 
 int /*<<< orphan*/  nfs_set_pageerror (struct page*) ; 
 int nfs_writepage_setup (struct nfs_open_context*,struct page*,unsigned int,unsigned int) ; 
 scalar_t__ page_offset (struct page*) ; 

int nfs_updatepage(struct file *file, struct page *page,
		unsigned int offset, unsigned int count)
{
	struct nfs_open_context *ctx = nfs_file_open_context(file);
	struct inode	*inode = page->mapping->host;
	int		status = 0;

	nfs_inc_stats(inode, NFSIOS_VFSUPDATEPAGE);

	dprintk("NFS:       nfs_updatepage(%s/%s %d@%lld)\n",
		file->f_path.dentry->d_parent->d_name.name,
		file->f_path.dentry->d_name.name, count,
		(long long)(page_offset(page) + offset));

	if (nfs_can_extend_write(file, page, inode)) {
		count = max(count + offset, nfs_page_length(page));
		offset = 0;
	}

	status = nfs_writepage_setup(ctx, page, offset, count);
	if (status < 0)
		nfs_set_pageerror(page);

	dprintk("NFS:       nfs_updatepage returns %d (isize %lld)\n",
			status, (long long)i_size_read(inode));
	return status;
}