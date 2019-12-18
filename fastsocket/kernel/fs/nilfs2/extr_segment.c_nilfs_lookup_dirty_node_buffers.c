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
struct pagevec {int /*<<< orphan*/ * pages; } ;
struct address_space {int dummy; } ;
struct nilfs_inode_info {struct address_space i_btnode_cache; } ;
struct list_head {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {struct buffer_head* b_this_page; int /*<<< orphan*/  b_assoc_buffers; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 struct nilfs_inode_info* NILFS_I (struct inode*) ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int /*<<< orphan*/  PAGEVEC_SIZE ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 struct buffer_head* page_buffers (int /*<<< orphan*/ ) ; 
 unsigned int pagevec_count (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*,int /*<<< orphan*/ ) ; 
 scalar_t__ pagevec_lookup_tag (struct pagevec*,struct address_space*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pagevec_release (struct pagevec*) ; 

__attribute__((used)) static void nilfs_lookup_dirty_node_buffers(struct inode *inode,
					    struct list_head *listp)
{
	struct nilfs_inode_info *ii = NILFS_I(inode);
	struct address_space *mapping = &ii->i_btnode_cache;
	struct pagevec pvec;
	struct buffer_head *bh, *head;
	unsigned int i;
	pgoff_t index = 0;

	pagevec_init(&pvec, 0);

	while (pagevec_lookup_tag(&pvec, mapping, &index, PAGECACHE_TAG_DIRTY,
				  PAGEVEC_SIZE)) {
		for (i = 0; i < pagevec_count(&pvec); i++) {
			bh = head = page_buffers(pvec.pages[i]);
			do {
				if (buffer_dirty(bh)) {
					get_bh(bh);
					list_add_tail(&bh->b_assoc_buffers,
						      listp);
				}
				bh = bh->b_this_page;
			} while (bh != head);
		}
		pagevec_release(&pvec);
		cond_resched();
	}
}