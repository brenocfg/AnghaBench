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
struct TYPE_2__ {int /*<<< orphan*/  de_num_used; struct ocfs2_dx_entry* de_entries; } ;
struct ocfs2_dx_leaf {TYPE_1__ dl_list; } ;
struct ocfs2_dx_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocfs2_dx_dir_leaf_insert_tail(struct ocfs2_dx_leaf *dx_leaf,
					  struct ocfs2_dx_entry *dx_new_entry)
{
	int i;

	i = le16_to_cpu(dx_leaf->dl_list.de_num_used);
	dx_leaf->dl_list.de_entries[i] = *dx_new_entry;

	le16_add_cpu(&dx_leaf->dl_list.de_num_used, 1);
}