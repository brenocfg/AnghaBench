#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtree_t ;
struct TYPE_5__ {int /*<<< orphan*/  child; } ;
typedef  TYPE_1__ rtree_node_elm_t ;

/* Variables and functions */
 TYPE_1__* rtree_node_init (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 

rtree_node_elm_t *
rtree_child_read_hard(rtree_t *rtree, rtree_node_elm_t *elm, unsigned level)
{

	return (rtree_node_init(rtree, level, &elm->child));
}