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
typedef  union afs_dirent {int dummy; } afs_dirent ;
typedef  union afs_dir_block {int dummy; } afs_dir_block ;
struct page {int dummy; } ;
struct key {int dummy; } ;
struct inode {unsigned int i_size; int /*<<< orphan*/  i_ino; } ;
struct afs_dir_page {union afs_dir_block* blocks; } ;
typedef  int /*<<< orphan*/  filldir_t ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 TYPE_1__* AFS_FS_I (struct inode*) ; 
 int /*<<< orphan*/  AFS_VNODE_DELETED ; 
 int ESTALE ; 
 scalar_t__ IS_ERR (struct page*) ; 
 unsigned int PAGE_SIZE ; 
 int PTR_ERR (struct page*) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 struct page* afs_dir_get_page (struct inode*,unsigned int,struct key*) ; 
 int afs_dir_iterate_block (unsigned int*,union afs_dir_block*,unsigned int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_dir_put_page (struct page*) ; 
 struct afs_dir_page* page_address (struct page*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int afs_dir_iterate(struct inode *dir, unsigned *fpos, void *cookie,
			   filldir_t filldir, struct key *key)
{
	union afs_dir_block *dblock;
	struct afs_dir_page *dbuf;
	struct page *page;
	unsigned blkoff, limit;
	int ret;

	_enter("{%lu},%u,,", dir->i_ino, *fpos);

	if (test_bit(AFS_VNODE_DELETED, &AFS_FS_I(dir)->flags)) {
		_leave(" = -ESTALE");
		return -ESTALE;
	}

	/* round the file position up to the next entry boundary */
	*fpos += sizeof(union afs_dirent) - 1;
	*fpos &= ~(sizeof(union afs_dirent) - 1);

	/* walk through the blocks in sequence */
	ret = 0;
	while (*fpos < dir->i_size) {
		blkoff = *fpos & ~(sizeof(union afs_dir_block) - 1);

		/* fetch the appropriate page from the directory */
		page = afs_dir_get_page(dir, blkoff / PAGE_SIZE, key);
		if (IS_ERR(page)) {
			ret = PTR_ERR(page);
			break;
		}

		limit = blkoff & ~(PAGE_SIZE - 1);

		dbuf = page_address(page);

		/* deal with the individual blocks stashed on this page */
		do {
			dblock = &dbuf->blocks[(blkoff % PAGE_SIZE) /
					       sizeof(union afs_dir_block)];
			ret = afs_dir_iterate_block(fpos, dblock, blkoff,
						    cookie, filldir);
			if (ret != 1) {
				afs_dir_put_page(page);
				goto out;
			}

			blkoff += sizeof(union afs_dir_block);

		} while (*fpos < dir->i_size && blkoff < limit);

		afs_dir_put_page(page);
		ret = 0;
	}

out:
	_leave(" = %d", ret);
	return ret;
}