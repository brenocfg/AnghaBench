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
struct mtdblk_dev {int dummy; } ;
struct mtd_blktrans_dev {size_t devnum; } ;

/* Variables and functions */
 int do_cached_read (struct mtdblk_dev*,unsigned long,int,char*) ; 
 struct mtdblk_dev** mtdblks ; 

__attribute__((used)) static int mtdblock_readsect(struct mtd_blktrans_dev *dev,
			      unsigned long block, char *buf)
{
	struct mtdblk_dev *mtdblk = mtdblks[dev->devnum];
	return do_cached_read(mtdblk, block<<9, 512, buf);
}