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
struct fsnotify_group {int /*<<< orphan*/  num_marks; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsnotify_clear_marks_by_group (struct fsnotify_group*) ; 
 int /*<<< orphan*/  fsnotify_final_destroy_group (struct fsnotify_group*) ; 

__attribute__((used)) static void fsnotify_destroy_group(struct fsnotify_group *group)
{
	/* clear all inode mark entries for this group */
	fsnotify_clear_marks_by_group(group);

	/* past the point of no return, matches the initial value of 1 */
	if (atomic_dec_and_test(&group->num_marks))
		fsnotify_final_destroy_group(group);
}