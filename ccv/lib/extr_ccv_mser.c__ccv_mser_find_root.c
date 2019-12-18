#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* shortcut; } ;
typedef  TYPE_1__ ccv_mser_node_t ;

/* Variables and functions */

__attribute__((used)) static ccv_mser_node_t* _ccv_mser_find_root(ccv_mser_node_t* node)
{
	ccv_mser_node_t* prev = node;
	ccv_mser_node_t* root;
	for (;;)
	{
		root = node->shortcut;
		// use the shortcut as a temporary variable to record previous node,
		// we will update it again shortly with the real shortcut to root
		node->shortcut = prev;
		if (root == node)
			break;
		prev = node;
		node = root;
	}
	for (;;)
	{
		prev = node->shortcut;
		node->shortcut = root;
		if (prev == node)
			break;
		node = prev;
	}
	return root;
}