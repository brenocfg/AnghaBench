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
struct snapshot_handle {scalar_t__ cur; scalar_t__ prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PG_UNSAFE_CLEAR ; 
 int /*<<< orphan*/  copy_last_highmem_page () ; 
 int /*<<< orphan*/  free_highmem_data () ; 
 int /*<<< orphan*/  memory_bm_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nr_copy_pages ; 
 scalar_t__ nr_meta_pages ; 
 int /*<<< orphan*/  orig_bm ; 

void snapshot_write_finalize(struct snapshot_handle *handle)
{
	copy_last_highmem_page();
	/* Free only if we have loaded the image entirely */
	if (handle->prev && handle->cur > nr_meta_pages + nr_copy_pages) {
		memory_bm_free(&orig_bm, PG_UNSAFE_CLEAR);
		free_highmem_data();
	}
}