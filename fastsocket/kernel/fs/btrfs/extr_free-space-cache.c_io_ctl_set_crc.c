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
typedef  scalar_t__ u32 ;
struct io_ctl {int num_pages; int /*<<< orphan*/ * pages; scalar_t__ orig; int /*<<< orphan*/  root; int /*<<< orphan*/  check_crcs; } ;

/* Variables and functions */
 scalar_t__ PAGE_CACHE_SIZE ; 
 scalar_t__ btrfs_csum_data (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_csum_final (scalar_t__,char*) ; 
 int /*<<< orphan*/  io_ctl_unmap_page (struct io_ctl*) ; 
 scalar_t__* kmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void io_ctl_set_crc(struct io_ctl *io_ctl, int index)
{
	u32 *tmp;
	u32 crc = ~(u32)0;
	unsigned offset = 0;

	if (!io_ctl->check_crcs) {
		io_ctl_unmap_page(io_ctl);
		return;
	}

	if (index == 0)
		offset = sizeof(u32) * io_ctl->num_pages;

	crc = btrfs_csum_data(io_ctl->root, io_ctl->orig + offset, crc,
			      PAGE_CACHE_SIZE - offset);
	btrfs_csum_final(crc, (char *)&crc);
	io_ctl_unmap_page(io_ctl);
	tmp = kmap(io_ctl->pages[0]);
	tmp += index;
	*tmp = crc;
	kunmap(io_ctl->pages[0]);
}