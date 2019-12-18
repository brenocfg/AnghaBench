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
struct TYPE_2__ {scalar_t__ time; } ;
union smb_dir_cache {TYPE_1__ head; } ;
struct smb_sb_info {int dummy; } ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 scalar_t__ SMB_MAX_AGE (struct smb_sb_info*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 struct page* grab_cache_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 union smb_dir_cache* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 struct smb_sb_info* server_from_inode (struct inode*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

void
smb_invalid_dir_cache(struct inode * dir)
{
	struct smb_sb_info *server = server_from_inode(dir);
	union  smb_dir_cache *cache = NULL;
	struct page *page = NULL;

	page = grab_cache_page(&dir->i_data, 0);
	if (!page)
		goto out;

	if (!PageUptodate(page))
		goto out_unlock;

	cache = kmap(page);
	cache->head.time = jiffies - SMB_MAX_AGE(server);

	kunmap(page);
	SetPageUptodate(page);
out_unlock:
	unlock_page(page);
	page_cache_release(page);
out:
	return;
}