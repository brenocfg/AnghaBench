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
struct reiserfs_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  reiserfs_warning (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static int errcatch_is_left_mergeable(struct reiserfs_key *key,
				      unsigned long bsize)
{
	reiserfs_warning(NULL, "green-16003",
			 "Invalid item type observed, run fsck ASAP");
	return 0;
}