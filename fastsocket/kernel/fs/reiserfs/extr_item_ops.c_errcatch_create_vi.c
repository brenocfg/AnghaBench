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
struct virtual_node {int dummy; } ;
struct virtual_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  reiserfs_warning (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static int errcatch_create_vi(struct virtual_node *vn,
			      struct virtual_item *vi,
			      int is_affected, int insert_size)
{
	reiserfs_warning(NULL, "green-16006",
			 "Invalid item type observed, run fsck ASAP");
	return 0;		// We might return -1 here as well, but it won't help as create_virtual_node() from where
	// this operation is called from is of return type void.
}