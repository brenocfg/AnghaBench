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
typedef  int /*<<< orphan*/  u_char ;
struct page {int dummy; } ;
struct block2mtd_dev {TYPE_2__* blkdev; } ;
struct address_space {int dummy; } ;
typedef  int loff_t ;
struct TYPE_4__ {TYPE_1__* bd_inode; } ;
struct TYPE_3__ {struct address_space* i_mapping; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int PTR_ERR (struct page*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 scalar_t__ memcmp (scalar_t__,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 struct page* page_read (struct address_space*,int) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int _block2mtd_write(struct block2mtd_dev *dev, const u_char *buf,
		loff_t to, size_t len, size_t *retlen)
{
	struct page *page;
	struct address_space *mapping = dev->blkdev->bd_inode->i_mapping;
	int index = to >> PAGE_SHIFT;	// page index
	int offset = to & ~PAGE_MASK;	// page offset
	int cpylen;

	if (retlen)
		*retlen = 0;
	while (len) {
		if ((offset+len) > PAGE_SIZE)
			cpylen = PAGE_SIZE - offset;	// multiple pages
		else
			cpylen = len;			// this page
		len = len - cpylen;

		page = page_read(mapping, index);
		if (!page)
			return -ENOMEM;
		if (IS_ERR(page))
			return PTR_ERR(page);

		if (memcmp(page_address(page)+offset, buf, cpylen)) {
			lock_page(page);
			memcpy(page_address(page) + offset, buf, cpylen);
			set_page_dirty(page);
			unlock_page(page);
		}
		page_cache_release(page);

		if (retlen)
			*retlen += cpylen;

		buf += cpylen;
		offset = 0;
		index++;
	}
	return 0;
}