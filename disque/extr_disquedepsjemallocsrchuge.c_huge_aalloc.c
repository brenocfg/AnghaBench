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
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/ * extent_node_arena_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  huge_node_get (void const*) ; 

arena_t *
huge_aalloc(const void *ptr)
{

	return (extent_node_arena_get(huge_node_get(ptr)));
}