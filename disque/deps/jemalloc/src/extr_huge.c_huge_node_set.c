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
typedef  int /*<<< orphan*/  extent_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int chunk_register (void const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_node_achunk_get (int /*<<< orphan*/ *) ; 
 void const* extent_node_addr_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
huge_node_set(const void *ptr, extent_node_t *node)
{

	assert(extent_node_addr_get(node) == ptr);
	assert(!extent_node_achunk_get(node));
	return (chunk_register(ptr, node));
}