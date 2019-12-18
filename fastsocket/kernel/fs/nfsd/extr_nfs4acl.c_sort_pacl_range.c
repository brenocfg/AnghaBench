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
struct posix_acl_entry {scalar_t__ e_id; } ;
struct posix_acl {struct posix_acl_entry* a_entries; } ;

/* Variables and functions */

__attribute__((used)) static void
sort_pacl_range(struct posix_acl *pacl, int start, int end) {
	int sorted = 0, i;
	struct posix_acl_entry tmp;

	/* We just do a bubble sort; easy to do in place, and we're not
	 * expecting acl's to be long enough to justify anything more. */
	while (!sorted) {
		sorted = 1;
		for (i = start; i < end; i++) {
			if (pacl->a_entries[i].e_id
					> pacl->a_entries[i+1].e_id) {
				sorted = 0;
				tmp = pacl->a_entries[i];
				pacl->a_entries[i] = pacl->a_entries[i+1];
				pacl->a_entries[i+1] = tmp;
			}
		}
	}
}