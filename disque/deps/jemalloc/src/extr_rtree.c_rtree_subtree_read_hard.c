#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* levels; } ;
typedef  TYPE_2__ rtree_t ;
typedef  int /*<<< orphan*/  rtree_node_elm_t ;
struct TYPE_5__ {int /*<<< orphan*/  subtree; } ;

/* Variables and functions */
 int /*<<< orphan*/ * rtree_node_init (TYPE_2__*,unsigned int,int /*<<< orphan*/ *) ; 

rtree_node_elm_t *
rtree_subtree_read_hard(rtree_t *rtree, unsigned level)
{

	return (rtree_node_init(rtree, level, &rtree->levels[level].subtree));
}