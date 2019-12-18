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
struct writeback_control {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int block_write_full_page (struct page*,int /*<<< orphan*/ ,struct writeback_control*) ; 
 int /*<<< orphan*/  mlog_entry (char*,struct page*) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  ocfs2_get_block ; 

__attribute__((used)) static int ocfs2_writepage(struct page *page, struct writeback_control *wbc)
{
	int ret;

	mlog_entry("(0x%p)\n", page);

	ret = block_write_full_page(page, ocfs2_get_block, wbc);

	mlog_exit(ret);

	return ret;
}