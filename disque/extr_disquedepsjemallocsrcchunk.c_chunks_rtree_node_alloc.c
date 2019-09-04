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
typedef  int /*<<< orphan*/  rtree_node_elm_t ;

/* Variables and functions */
 scalar_t__ base_alloc (size_t) ; 

__attribute__((used)) static rtree_node_elm_t *
chunks_rtree_node_alloc(size_t nelms)
{

	return ((rtree_node_elm_t *)base_alloc(nelms *
	    sizeof(rtree_node_elm_t)));
}