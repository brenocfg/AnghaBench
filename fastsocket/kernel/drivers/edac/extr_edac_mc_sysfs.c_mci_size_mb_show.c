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
struct mem_ctl_info {int nr_csrows; struct csrow_info* csrows; } ;
struct csrow_info {scalar_t__ nr_pages; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int PAGES_TO_MiB (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t mci_size_mb_show(struct mem_ctl_info *mci, char *data)
{
	int total_pages, csrow_idx;

	for (total_pages = csrow_idx = 0; csrow_idx < mci->nr_csrows;
		csrow_idx++) {
		struct csrow_info *csrow = &mci->csrows[csrow_idx];

		if (!csrow->nr_pages)
			continue;

		total_pages += csrow->nr_pages;
	}

	return sprintf(data, "%u\n", PAGES_TO_MiB(total_pages));
}