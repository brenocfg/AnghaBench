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
struct io_ctl {scalar_t__ cur; scalar_t__ orig; scalar_t__ index; scalar_t__ num_pages; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  io_ctl_map_page (struct io_ctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_ctl_set_crc (struct io_ctl*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int io_ctl_add_bitmap(struct io_ctl *io_ctl, void *bitmap)
{
	if (!io_ctl->cur)
		return -ENOSPC;

	/*
	 * If we aren't at the start of the current page, unmap this one and
	 * map the next one if there is any left.
	 */
	if (io_ctl->cur != io_ctl->orig) {
		io_ctl_set_crc(io_ctl, io_ctl->index - 1);
		if (io_ctl->index >= io_ctl->num_pages)
			return -ENOSPC;
		io_ctl_map_page(io_ctl, 0);
	}

	memcpy(io_ctl->cur, bitmap, PAGE_CACHE_SIZE);
	io_ctl_set_crc(io_ctl, io_ctl->index - 1);
	if (io_ctl->index < io_ctl->num_pages)
		io_ctl_map_page(io_ctl, 0);
	return 0;
}