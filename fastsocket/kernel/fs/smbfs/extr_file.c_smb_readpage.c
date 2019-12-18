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
struct page {int dummy; } ;
struct TYPE_2__ {struct dentry* dentry; } ;
struct file {TYPE_1__ f_path; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  page_cache_get (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int smb_readpage_sync (struct dentry*,struct page*) ; 

__attribute__((used)) static int
smb_readpage(struct file *file, struct page *page)
{
	int		error;
	struct dentry  *dentry = file->f_path.dentry;

	page_cache_get(page);
	error = smb_readpage_sync(dentry, page);
	page_cache_release(page);
	return error;
}