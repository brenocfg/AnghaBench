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
struct page_collect {unsigned int expected_pages; int pg_first; scalar_t__ length; scalar_t__ nr_pages; int /*<<< orphan*/ * bio; struct inode* inode; int /*<<< orphan*/  req_q; struct exofs_sb_info* sbi; } ;
struct inode {int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct exofs_sb_info {int /*<<< orphan*/  s_dev; } ;
struct TYPE_2__ {struct exofs_sb_info* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXOFS_DBGMSG (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  osd_request_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _pcol_init(struct page_collect *pcol, unsigned expected_pages,
		struct inode *inode)
{
	struct exofs_sb_info *sbi = inode->i_sb->s_fs_info;

	pcol->sbi = sbi;
	pcol->req_q = osd_request_queue(sbi->s_dev);
	pcol->inode = inode;
	pcol->expected_pages = expected_pages;

	pcol->bio = NULL;
	pcol->nr_pages = 0;
	pcol->length = 0;
	pcol->pg_first = -1;

	EXOFS_DBGMSG("_pcol_init ino=0x%lx expected_pages=%u\n", inode->i_ino,
		     expected_pages);
}