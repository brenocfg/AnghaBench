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
struct io_ctl {int /*<<< orphan*/  cur; int /*<<< orphan*/  index; } ;
struct btrfs_free_space {int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_CACHE_SIZE ; 
 int io_ctl_check_crc (struct io_ctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_ctl_unmap_page (struct io_ctl*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int io_ctl_read_bitmap(struct io_ctl *io_ctl,
			      struct btrfs_free_space *entry)
{
	int ret;

	ret = io_ctl_check_crc(io_ctl, io_ctl->index);
	if (ret)
		return ret;

	memcpy(entry->bitmap, io_ctl->cur, PAGE_CACHE_SIZE);
	io_ctl_unmap_page(io_ctl);

	return 0;
}