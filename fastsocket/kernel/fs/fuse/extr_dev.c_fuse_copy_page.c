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
struct fuse_copy_state {int /*<<< orphan*/  write; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_USER1 ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 unsigned int fuse_copy_do (struct fuse_copy_state*,void**,unsigned int*) ; 
 int fuse_copy_fill (struct fuse_copy_state*) ; 
 void* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int fuse_copy_page(struct fuse_copy_state *cs, struct page *page,
			  unsigned offset, unsigned count, int zeroing)
{
	if (page && zeroing && count < PAGE_SIZE) {
		void *mapaddr = kmap_atomic(page, KM_USER1);
		memset(mapaddr, 0, PAGE_SIZE);
		kunmap_atomic(mapaddr, KM_USER1);
	}
	while (count) {
		if (!cs->len) {
			int err = fuse_copy_fill(cs);
			if (err)
				return err;
		}
		if (page) {
			void *mapaddr = kmap_atomic(page, KM_USER1);
			void *buf = mapaddr + offset;
			offset += fuse_copy_do(cs, &buf, &count);
			kunmap_atomic(mapaddr, KM_USER1);
		} else
			offset += fuse_copy_do(cs, NULL, &count);
	}
	if (page && !cs->write)
		flush_dcache_page(page);
	return 0;
}