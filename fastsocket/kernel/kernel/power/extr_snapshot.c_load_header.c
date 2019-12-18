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
struct swsusp_info {scalar_t__ image_pages; scalar_t__ pages; } ;

/* Variables and functions */
 int check_header (struct swsusp_info*) ; 
 scalar_t__ nr_copy_pages ; 
 scalar_t__ nr_meta_pages ; 
 int /*<<< orphan*/ * restore_pblist ; 

__attribute__((used)) static int
load_header(struct swsusp_info *info)
{
	int error;

	restore_pblist = NULL;
	error = check_header(info);
	if (!error) {
		nr_copy_pages = info->image_pages;
		nr_meta_pages = info->pages - info->image_pages - 1;
	}
	return error;
}