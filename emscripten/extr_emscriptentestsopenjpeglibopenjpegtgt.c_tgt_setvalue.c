#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* nodes; } ;
typedef  TYPE_1__ opj_tgt_tree_t ;
struct TYPE_5__ {int value; struct TYPE_5__* parent; } ;
typedef  TYPE_2__ opj_tgt_node_t ;

/* Variables and functions */

void tgt_setvalue(opj_tgt_tree_t *tree, int leafno, int value) {
	opj_tgt_node_t *node;
	node = &tree->nodes[leafno];
	while (node && node->value > value) {
		node->value = value;
		node = node->parent;
	}
}