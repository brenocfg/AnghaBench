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
struct swap_map_handle {scalar_t__ k; struct swap_map_page* cur; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int __GFP_HIGH ; 
 int __GFP_WAIT ; 
 int bio_read_page (int /*<<< orphan*/ ,struct swap_map_page*,int /*<<< orphan*/ *) ; 
 scalar_t__ get_zeroed_page (int) ; 
 int /*<<< orphan*/  release_swap_reader (struct swap_map_handle*) ; 

__attribute__((used)) static int get_swap_reader(struct swap_map_handle *handle, sector_t start)
{
	int error;

	if (!start)
		return -EINVAL;

	handle->cur = (struct swap_map_page *)get_zeroed_page(__GFP_WAIT | __GFP_HIGH);
	if (!handle->cur)
		return -ENOMEM;

	error = bio_read_page(start, handle->cur, NULL);
	if (error) {
		release_swap_reader(handle);
		return error;
	}
	handle->k = 0;
	return 0;
}