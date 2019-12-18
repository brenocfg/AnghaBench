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
struct pohmelfs_sb {int /*<<< orphan*/  mcache_root; } ;
struct TYPE_2__ {scalar_t__ rb_parent_color; } ;
struct pohmelfs_mcache {TYPE_1__ mcache_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_erase (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pohmelfs_mcache_remove(struct pohmelfs_sb *psb, struct pohmelfs_mcache *m)
{
	if (m && m->mcache_entry.rb_parent_color) {
		rb_erase(&m->mcache_entry, &psb->mcache_root);
		m->mcache_entry.rb_parent_color = 0;
		return 1;
	}
	return 0;
}