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
struct page {int dummy; } ;
struct key {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_ino; } ;
struct file {struct key* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 struct page* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct page*) ; 
 int /*<<< orphan*/  PageChecked (struct page*) ; 
 scalar_t__ PageError (struct page*) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  afs_dir_check_page (struct inode*,struct page*) ; 
 int /*<<< orphan*/  afs_dir_put_page (struct page*) ; 
 int /*<<< orphan*/  kmap (struct page*) ; 
 struct page* read_mapping_page (int /*<<< orphan*/ ,unsigned long,struct file*) ; 

__attribute__((used)) static struct page *afs_dir_get_page(struct inode *dir, unsigned long index,
				     struct key *key)
{
	struct page *page;
	struct file file = {
		.private_data = key,
	};

	_enter("{%lu},%lu", dir->i_ino, index);

	page = read_mapping_page(dir->i_mapping, index, &file);
	if (!IS_ERR(page)) {
		kmap(page);
		if (!PageChecked(page))
			afs_dir_check_page(dir, page);
		if (PageError(page))
			goto fail;
	}
	return page;

fail:
	afs_dir_put_page(page);
	_leave(" = -EIO");
	return ERR_PTR(-EIO);
}