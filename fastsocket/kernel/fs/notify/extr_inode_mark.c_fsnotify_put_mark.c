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
struct fsnotify_mark_entry {int /*<<< orphan*/  (* free_mark ) (struct fsnotify_mark_entry*) ;int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fsnotify_mark_entry*) ; 

void fsnotify_put_mark(struct fsnotify_mark_entry *entry)
{
	if (atomic_dec_and_test(&entry->refcnt))
		entry->free_mark(entry);
}