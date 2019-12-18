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
typedef  int /*<<< orphan*/  u64 ;
struct io_ctl {int size; scalar_t__ index; scalar_t__ num_pages; struct btrfs_free_space_entry* cur; } ;
struct btrfs_free_space_entry {int /*<<< orphan*/  type; void* bytes; void* offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FREE_SPACE_BITMAP ; 
 int /*<<< orphan*/  BTRFS_FREE_SPACE_EXTENT ; 
 int ENOSPC ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_ctl_map_page (struct io_ctl*,int) ; 
 int /*<<< orphan*/  io_ctl_set_crc (struct io_ctl*,scalar_t__) ; 

__attribute__((used)) static int io_ctl_add_entry(struct io_ctl *io_ctl, u64 offset, u64 bytes,
			    void *bitmap)
{
	struct btrfs_free_space_entry *entry;

	if (!io_ctl->cur)
		return -ENOSPC;

	entry = io_ctl->cur;
	entry->offset = cpu_to_le64(offset);
	entry->bytes = cpu_to_le64(bytes);
	entry->type = (bitmap) ? BTRFS_FREE_SPACE_BITMAP :
		BTRFS_FREE_SPACE_EXTENT;
	io_ctl->cur += sizeof(struct btrfs_free_space_entry);
	io_ctl->size -= sizeof(struct btrfs_free_space_entry);

	if (io_ctl->size >= sizeof(struct btrfs_free_space_entry))
		return 0;

	io_ctl_set_crc(io_ctl, io_ctl->index - 1);

	/* No more pages to map */
	if (io_ctl->index >= io_ctl->num_pages)
		return 0;

	/* map the next page */
	io_ctl_map_page(io_ctl, 1);
	return 0;
}