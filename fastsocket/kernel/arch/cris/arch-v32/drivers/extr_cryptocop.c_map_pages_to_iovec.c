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
struct iovec {unsigned char* iov_base; int iov_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG_API (int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  printk (char*,int,...) ; 

__attribute__((used)) static int map_pages_to_iovec(struct iovec *iov, int iovlen, int *iovix, struct page **pages, int nopages, int *pageix, int *pageoffset, int map_length )
{
	int tmplen;

	assert(iov != NULL);
	assert(iovix != NULL);
	assert(pages != NULL);
	assert(pageix != NULL);
	assert(pageoffset != NULL);

	DEBUG(printk("map_pages_to_iovec, map_length=%d, iovlen=%d, *iovix=%d, nopages=%d, *pageix=%d, *pageoffset=%d\n", map_length, iovlen, *iovix, nopages, *pageix, *pageoffset));

	while (map_length > 0){
		DEBUG(printk("map_pages_to_iovec, map_length=%d, iovlen=%d, *iovix=%d, nopages=%d, *pageix=%d, *pageoffset=%d\n", map_length, iovlen, *iovix, nopages, *pageix, *pageoffset));
		if (*iovix >= iovlen){
			DEBUG_API(printk("map_page_to_iovec: *iovix=%d >= iovlen=%d\n", *iovix, iovlen));
			return 0;
		}
		if (*pageix >= nopages){
			DEBUG_API(printk("map_page_to_iovec: *pageix=%d >= nopages=%d\n", *pageix, nopages));
			return 0;
		}
		iov[*iovix].iov_base = (unsigned char*)page_address(pages[*pageix]) + *pageoffset;
		tmplen = PAGE_SIZE - *pageoffset;
		if (tmplen < map_length){
			(*pageoffset) = 0;
			(*pageix)++;
		} else {
			tmplen = map_length;
			(*pageoffset) += map_length;
		}
		DEBUG(printk("mapping %d bytes from page %d (or %d) to iovec %d\n", tmplen, *pageix, *pageix-1, *iovix));
		iov[*iovix].iov_len = tmplen;
		map_length -= tmplen;
		(*iovix)++;
	}
	DEBUG(printk("map_page_to_iovec, exit, *iovix=%d\n", *iovix));
	return -1;
}