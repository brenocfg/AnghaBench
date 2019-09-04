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
struct TYPE_5__ {int low; int value; struct TYPE_5__* parent; } ;
typedef  TYPE_2__ opj_tgt_node_t ;
typedef  int /*<<< orphan*/  opj_bio_t ;

/* Variables and functions */
 scalar_t__ bio_read (int /*<<< orphan*/ *,int) ; 

int tgt_decode(opj_bio_t *bio, opj_tgt_tree_t *tree, int leafno, int threshold) {
	opj_tgt_node_t *stk[31];
	opj_tgt_node_t **stkptr;
	opj_tgt_node_t *node;
	int low;

	stkptr = stk;
	node = &tree->nodes[leafno];
	while (node->parent) {
		*stkptr++ = node;
		node = node->parent;
	}
	
	low = 0;
	for (;;) {
		if (low > node->low) {
			node->low = low;
		} else {
			low = node->low;
		}
		while (low < threshold && low < node->value) {
			if (bio_read(bio, 1)) {
				node->value = low;
			} else {
				++low;
			}
		}
		node->low = low;
		if (stkptr == stk) {
			break;
		}
		node = *--stkptr;
	}
	
	return (node->value < threshold) ? 1 : 0;
}