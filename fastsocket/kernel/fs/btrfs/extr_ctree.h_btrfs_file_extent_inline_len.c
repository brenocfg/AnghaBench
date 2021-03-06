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
typedef  int /*<<< orphan*/  u32 ;
struct extent_buffer {int dummy; } ;
struct btrfs_file_extent_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_file_extent_ram_bytes (struct extent_buffer*,struct btrfs_file_extent_item*) ; 

__attribute__((used)) static inline u32 btrfs_file_extent_inline_len(struct extent_buffer *eb,
					       struct btrfs_file_extent_item *e)
{
	return btrfs_file_extent_ram_bytes(eb, e);
}