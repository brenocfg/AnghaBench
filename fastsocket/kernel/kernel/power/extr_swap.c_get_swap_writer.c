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
struct swap_map_page {int dummy; } ;
struct swap_map_handle {scalar_t__ k; int /*<<< orphan*/  cur_swap; struct swap_map_page* cur; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  alloc_swapdev_block (int /*<<< orphan*/ ) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_swap_writer (struct swap_map_handle*) ; 
 int /*<<< orphan*/  root_swap ; 

__attribute__((used)) static int get_swap_writer(struct swap_map_handle *handle)
{
	handle->cur = (struct swap_map_page *)get_zeroed_page(GFP_KERNEL);
	if (!handle->cur)
		return -ENOMEM;
	handle->cur_swap = alloc_swapdev_block(root_swap);
	if (!handle->cur_swap) {
		release_swap_writer(handle);
		return -ENOSPC;
	}
	handle->k = 0;
	return 0;
}