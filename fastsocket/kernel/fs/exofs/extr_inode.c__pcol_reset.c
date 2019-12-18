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
struct page_collect {int expected_pages; int pg_first; TYPE_1__* inode; scalar_t__ length; scalar_t__ nr_pages; int /*<<< orphan*/ * bio; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXOFS_DBGMSG (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ min (scalar_t__,int) ; 

__attribute__((used)) static void _pcol_reset(struct page_collect *pcol)
{
	pcol->expected_pages -= min(pcol->nr_pages, pcol->expected_pages);

	pcol->bio = NULL;
	pcol->nr_pages = 0;
	pcol->length = 0;
	pcol->pg_first = -1;
	EXOFS_DBGMSG("_pcol_reset ino=0x%lx expected_pages=%u\n",
		     pcol->inode->i_ino, pcol->expected_pages);

	/* this is probably the end of the loop but in writes
	 * it might not end here. don't be left with nothing
	 */
	if (!pcol->expected_pages)
		pcol->expected_pages = 128;
}