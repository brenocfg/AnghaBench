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
struct TYPE_3__ {scalar_t__ val; struct TYPE_3__* parent; } ;
typedef  TYPE_1__ Jpeg2000TgtNode ;

/* Variables and functions */

__attribute__((used)) static void tag_tree_update(Jpeg2000TgtNode *node)
{
    int lev = 0;
    while (node->parent){
        if (node->parent->val <= node->val)
            break;
        node->parent->val = node->val;
        node = node->parent;
        lev++;
    }
}