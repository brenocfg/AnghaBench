#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct page {int dummy; } ;
struct address_space {int dummy; } ;
typedef  scalar_t__ s64 ;
typedef  int pgoff_t ;
struct TYPE_5__ {scalar_t__ nr_clusters; int /*<<< orphan*/  lcnbmp_lock; TYPE_1__* lcnbmp_ino; } ;
typedef  TYPE_2__ ntfs_volume ;
struct TYPE_4__ {struct address_space* i_mapping; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct page*) ; 
 int /*<<< orphan*/  KM_USER0 ; 
 int PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ hweight32 (int /*<<< orphan*/ ) ; 
 scalar_t__ kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntfs_debug (char*,...) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 struct page* read_mapping_page (struct address_space*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static s64 get_nr_free_clusters(ntfs_volume *vol)
{
	s64 nr_free = vol->nr_clusters;
	u32 *kaddr;
	struct address_space *mapping = vol->lcnbmp_ino->i_mapping;
	struct page *page;
	pgoff_t index, max_index;

	ntfs_debug("Entering.");
	/* Serialize accesses to the cluster bitmap. */
	down_read(&vol->lcnbmp_lock);
	/*
	 * Convert the number of bits into bytes rounded up, then convert into
	 * multiples of PAGE_CACHE_SIZE, rounding up so that if we have one
	 * full and one partial page max_index = 2.
	 */
	max_index = (((vol->nr_clusters + 7) >> 3) + PAGE_CACHE_SIZE - 1) >>
			PAGE_CACHE_SHIFT;
	/* Use multiples of 4 bytes, thus max_size is PAGE_CACHE_SIZE / 4. */
	ntfs_debug("Reading $Bitmap, max_index = 0x%lx, max_size = 0x%lx.",
			max_index, PAGE_CACHE_SIZE / 4);
	for (index = 0; index < max_index; index++) {
		unsigned int i;
		/*
		 * Read the page from page cache, getting it from backing store
		 * if necessary, and increment the use count.
		 */
		page = read_mapping_page(mapping, index, NULL);
		/* Ignore pages which errored synchronously. */
		if (IS_ERR(page)) {
			ntfs_debug("read_mapping_page() error. Skipping "
					"page (index 0x%lx).", index);
			nr_free -= PAGE_CACHE_SIZE * 8;
			continue;
		}
		kaddr = (u32*)kmap_atomic(page, KM_USER0);
		/*
		 * For each 4 bytes, subtract the number of set bits. If this
		 * is the last page and it is partial we don't really care as
		 * it just means we do a little extra work but it won't affect
		 * the result as all out of range bytes are set to zero by
		 * ntfs_readpage().
		 */
	  	for (i = 0; i < PAGE_CACHE_SIZE / 4; i++)
			nr_free -= (s64)hweight32(kaddr[i]);
		kunmap_atomic(kaddr, KM_USER0);
		page_cache_release(page);
	}
	ntfs_debug("Finished reading $Bitmap, last index = 0x%lx.", index - 1);
	/*
	 * Fixup for eventual bits outside logical ntfs volume (see function
	 * description above).
	 */
	if (vol->nr_clusters & 63)
		nr_free += 64 - (vol->nr_clusters & 63);
	up_read(&vol->lcnbmp_lock);
	/* If errors occured we may well have gone below zero, fix this. */
	if (nr_free < 0)
		nr_free = 0;
	ntfs_debug("Exiting.");
	return nr_free;
}