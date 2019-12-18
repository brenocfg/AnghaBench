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
struct address_space {int /*<<< orphan*/  private_list; int /*<<< orphan*/  private_lock; struct address_space* assoc_mapping; } ;

/* Variables and functions */
 int fsync_buffers_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

int sync_mapping_buffers(struct address_space *mapping)
{
	struct address_space *buffer_mapping = mapping->assoc_mapping;

	if (buffer_mapping == NULL || list_empty(&mapping->private_list))
		return 0;

	return fsync_buffers_list(&buffer_mapping->private_lock,
					&mapping->private_list);
}