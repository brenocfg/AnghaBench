#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  node_t ;
struct TYPE_3__ {int /*<<< orphan*/ ** freelist; int /*<<< orphan*/  blocPtrs; int /*<<< orphan*/ ** nodePtrs; } ;
typedef  TYPE_1__ huff_t ;

/* Variables and functions */

__attribute__((used)) static node_t **get_ppnode(huff_t* huff) {
	node_t **tppnode;
	if (!huff->freelist) {
		return &(huff->nodePtrs[huff->blocPtrs++]);
	} else {
		tppnode = huff->freelist;
		huff->freelist = (node_t **)*tppnode;
		return tppnode;
	}
}