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
struct filter_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct filter_entry* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_entries ; 
 int /*<<< orphan*/  free (struct filter_entry*) ; 
 int /*<<< orphan*/  nm_out_filter ; 

__attribute__((used)) static void
filter_dest(void)
{
	struct filter_entry *e;

	while (!SLIST_EMPTY(&nm_out_filter)) {
		e = SLIST_FIRST(&nm_out_filter);
		SLIST_REMOVE_HEAD(&nm_out_filter, filter_entries);
		free(e);
	}
}