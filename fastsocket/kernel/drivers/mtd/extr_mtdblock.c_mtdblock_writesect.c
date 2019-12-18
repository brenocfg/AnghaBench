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
struct mtdblk_dev {scalar_t__ cache_data; TYPE_1__* mtd; scalar_t__ cache_size; } ;
struct mtd_blktrans_dev {size_t devnum; } ;
struct TYPE_2__ {int /*<<< orphan*/  erasesize; } ;

/* Variables and functions */
 int EINTR ; 
 int do_cached_write (struct mtdblk_dev*,unsigned long,int,char*) ; 
 struct mtdblk_dev** mtdblks ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtdblock_writesect(struct mtd_blktrans_dev *dev,
			      unsigned long block, char *buf)
{
	struct mtdblk_dev *mtdblk = mtdblks[dev->devnum];
	if (unlikely(!mtdblk->cache_data && mtdblk->cache_size)) {
		mtdblk->cache_data = vmalloc(mtdblk->mtd->erasesize);
		if (!mtdblk->cache_data)
			return -EINTR;
		/* -EINTR is not really correct, but it is the best match
		 * documented in man 2 write for all cases.  We could also
		 * return -EAGAIN sometimes, but why bother?
		 */
	}
	return do_cached_write(mtdblk, block<<9, 512, buf);
}