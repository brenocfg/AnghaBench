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
struct writeback_control {int dummy; } ;
struct page_collect {int dummy; } ;
struct page {TYPE_1__* mapping; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXOFS_ERR (char*,int) ; 
 int /*<<< orphan*/  _pcol_init (struct page_collect*,int,int /*<<< orphan*/ ) ; 
 int write_exec (struct page_collect*) ; 
 int writepage_strip (struct page*,int /*<<< orphan*/ *,struct page_collect*) ; 

__attribute__((used)) static int exofs_writepage(struct page *page, struct writeback_control *wbc)
{
	struct page_collect pcol;
	int ret;

	_pcol_init(&pcol, 1, page->mapping->host);

	ret = writepage_strip(page, NULL, &pcol);
	if (ret) {
		EXOFS_ERR("exofs_writepage => %d\n", ret);
		return ret;
	}

	return write_exec(&pcol);
}