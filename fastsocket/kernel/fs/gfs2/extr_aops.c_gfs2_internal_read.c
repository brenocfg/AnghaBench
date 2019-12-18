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
struct TYPE_2__ {struct address_space* i_mapping; } ;
struct gfs2_inode {TYPE_1__ i_inode; } ;
struct file_ra_state {int dummy; } ;
struct address_space {int dummy; } ;
typedef  int loff_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct page*) ; 
 int /*<<< orphan*/  KM_USER0 ; 
 int PAGE_CACHE_SIZE ; 
 int PTR_ERR (struct page*) ; 
 int /*<<< orphan*/  __gfs2_readpage ; 
 void* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_page_accessed (struct page*) ; 
 int /*<<< orphan*/  memcpy (char*,void*,unsigned int) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 struct page* read_cache_page (struct address_space*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int gfs2_internal_read(struct gfs2_inode *ip, struct file_ra_state *ra_state,
                       char *buf, loff_t *pos, unsigned size)
{
	struct address_space *mapping = ip->i_inode.i_mapping;
	unsigned long index = *pos / PAGE_CACHE_SIZE;
	unsigned offset = *pos & (PAGE_CACHE_SIZE - 1);
	unsigned copied = 0;
	unsigned amt;
	struct page *page;
	void *p;

	do {
		amt = size - copied;
		if (offset + size > PAGE_CACHE_SIZE)
			amt = PAGE_CACHE_SIZE - offset;
		page = read_cache_page(mapping, index, __gfs2_readpage, NULL);
		if (IS_ERR(page))
			return PTR_ERR(page);
		p = kmap_atomic(page, KM_USER0);
		memcpy(buf + copied, p + offset, amt);
		kunmap_atomic(p, KM_USER0);
		mark_page_accessed(page);
		page_cache_release(page);
		copied += amt;
		index++;
		offset = 0;
	} while(copied < size);
	(*pos) += size;
	return size;
}