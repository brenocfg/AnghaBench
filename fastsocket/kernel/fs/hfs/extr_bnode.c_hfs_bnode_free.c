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
struct hfs_bnode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hfs_bnode*) ; 

void hfs_bnode_free(struct hfs_bnode *node)
{
	//int i;

	//for (i = 0; i < node->tree->pages_per_bnode; i++)
	//	if (node->page[i])
	//		page_cache_release(node->page[i]);
	kfree(node);
}