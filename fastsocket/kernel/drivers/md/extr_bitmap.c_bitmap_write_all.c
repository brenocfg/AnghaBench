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
struct TYPE_2__ {int file_pages; scalar_t__ file; int /*<<< orphan*/  filemap; } ;
struct bitmap {scalar_t__ allclean; TYPE_1__ storage; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_PAGE_NEEDWRITE ; 
 int /*<<< orphan*/  set_page_attr (struct bitmap*,int,int /*<<< orphan*/ ) ; 

void bitmap_write_all(struct bitmap *bitmap)
{
	/* We don't actually write all bitmap blocks here,
	 * just flag them as needing to be written
	 */
	int i;

	if (!bitmap || !bitmap->storage.filemap)
		return;
	if (bitmap->storage.file)
		/* Only one copy, so nothing needed */
		return;

	for (i = 0; i < bitmap->storage.file_pages; i++)
		set_page_attr(bitmap, i,
			      BITMAP_PAGE_NEEDWRITE);
	bitmap->allclean = 0;
}