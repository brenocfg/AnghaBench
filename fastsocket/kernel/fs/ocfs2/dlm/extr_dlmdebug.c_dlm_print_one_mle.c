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
struct dlm_master_list_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  dump_mle (struct dlm_master_list_entry*,char*,scalar_t__) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 

void dlm_print_one_mle(struct dlm_master_list_entry *mle)
{
	char *buf;

	buf = (char *) get_zeroed_page(GFP_NOFS);
	if (buf) {
		dump_mle(mle, buf, PAGE_SIZE - 1);
		free_page((unsigned long)buf);
	}
}