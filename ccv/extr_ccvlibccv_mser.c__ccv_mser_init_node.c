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
struct TYPE_4__ {int x; int y; } ;
struct TYPE_5__ {int root; TYPE_1__ point; struct TYPE_5__* shortcut; struct TYPE_5__* next; struct TYPE_5__* prev; } ;
typedef  TYPE_2__ ccv_mser_node_t ;

/* Variables and functions */

__attribute__((used)) static void _ccv_mser_init_node(ccv_mser_node_t* node, int x, int y)
{
	node->prev = node->next = node->shortcut = node; // endless double link list
	node->point.x = x;
	node->point.y = y;
	node->root = -1;
}