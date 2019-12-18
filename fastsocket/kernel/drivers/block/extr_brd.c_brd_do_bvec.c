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
struct brd_device {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_USER0 ; 
 int READ ; 
 int /*<<< orphan*/  copy_from_brd (void*,struct brd_device*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  copy_to_brd (struct brd_device*,void*,int /*<<< orphan*/ ,unsigned int) ; 
 int copy_to_brd_setup (struct brd_device*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 void* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brd_do_bvec(struct brd_device *brd, struct page *page,
			unsigned int len, unsigned int off, int rw,
			sector_t sector)
{
	void *mem;
	int err = 0;

	if (rw != READ) {
		err = copy_to_brd_setup(brd, sector, len);
		if (err)
			goto out;
	}

	mem = kmap_atomic(page, KM_USER0);
	if (rw == READ) {
		copy_from_brd(mem + off, brd, sector, len);
		flush_dcache_page(page);
	} else {
		flush_dcache_page(page);
		copy_to_brd(brd, mem + off, sector, len);
	}
	kunmap_atomic(mem, KM_USER0);

out:
	return err;
}