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
struct ubifs_znode {int child_cnt; TYPE_1__* zbranch; } ;
struct TYPE_2__ {struct ubifs_znode* znode; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ubifs_znode *
ubifs_tnc_find_child(struct ubifs_znode *znode, int start)
{
	while (start < znode->child_cnt) {
		if (znode->zbranch[start].znode)
			return znode->zbranch[start].znode;
		start += 1;
	}

	return NULL;
}