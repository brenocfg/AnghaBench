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
struct buffer_head {int /*<<< orphan*/ * b_assoc_map; int /*<<< orphan*/  b_assoc_buffers; TYPE_1__* b_page; } ;
struct address_space {int /*<<< orphan*/  private_lock; } ;
struct TYPE_2__ {struct address_space* mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  __brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void __bforget(struct buffer_head *bh)
{
	clear_buffer_dirty(bh);
	if (bh->b_assoc_map) {
		struct address_space *buffer_mapping = bh->b_page->mapping;

		spin_lock(&buffer_mapping->private_lock);
		list_del_init(&bh->b_assoc_buffers);
		bh->b_assoc_map = NULL;
		spin_unlock(&buffer_mapping->private_lock);
	}
	__brelse(bh);
}