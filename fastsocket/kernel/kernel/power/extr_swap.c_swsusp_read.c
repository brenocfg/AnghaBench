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
struct swsusp_info {scalar_t__ pages; } ;
struct swap_map_handle {int dummy; } ;
struct snapshot_handle {int dummy; } ;
struct TYPE_2__ {unsigned int flags; int /*<<< orphan*/  image; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ data_of (struct snapshot_handle) ; 
 int get_swap_reader (struct swap_map_handle*,int /*<<< orphan*/ ) ; 
 int load_image (struct swap_map_handle*,struct snapshot_handle*,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct snapshot_handle*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  release_swap_reader (struct swap_map_handle*) ; 
 int /*<<< orphan*/  resume_bdev ; 
 int snapshot_write_next (struct snapshot_handle*,int) ; 
 int swap_read_page (struct swap_map_handle*,struct swsusp_info*,int /*<<< orphan*/ *) ; 
 TYPE_1__* swsusp_header ; 

int swsusp_read(unsigned int *flags_p)
{
	int error;
	struct swap_map_handle handle;
	struct snapshot_handle snapshot;
	struct swsusp_info *header;

	*flags_p = swsusp_header->flags;
	if (IS_ERR(resume_bdev)) {
		pr_debug("PM: Image device not initialised\n");
		return PTR_ERR(resume_bdev);
	}

	memset(&snapshot, 0, sizeof(struct snapshot_handle));
	error = snapshot_write_next(&snapshot, PAGE_SIZE);
	if (error < PAGE_SIZE)
		return error < 0 ? error : -EFAULT;
	header = (struct swsusp_info *)data_of(snapshot);
	error = get_swap_reader(&handle, swsusp_header->image);
	if (!error)
		error = swap_read_page(&handle, header, NULL);
	if (!error)
		error = load_image(&handle, &snapshot, header->pages - 1);
	release_swap_reader(&handle);

	if (!error)
		pr_debug("PM: Image successfully loaded\n");
	else
		pr_debug("PM: Error %d resuming\n", error);
	return error;
}