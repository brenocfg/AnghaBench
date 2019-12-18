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
struct ocfs2_dx_entry_list {int /*<<< orphan*/  de_num_used; int /*<<< orphan*/ * de_entries; } ;
struct ocfs2_dx_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ocfs2_dx_list_remove_entry(struct ocfs2_dx_entry_list *entry_list,
				       int index)
{
	int num_used = le16_to_cpu(entry_list->de_num_used);

	if (num_used == 1 || index == (num_used - 1))
		goto clear;

	memmove(&entry_list->de_entries[index],
		&entry_list->de_entries[index + 1],
		(num_used - index - 1)*sizeof(struct ocfs2_dx_entry));
clear:
	num_used--;
	memset(&entry_list->de_entries[num_used], 0,
	       sizeof(struct ocfs2_dx_entry));
	entry_list->de_num_used = cpu_to_le16(num_used);
}