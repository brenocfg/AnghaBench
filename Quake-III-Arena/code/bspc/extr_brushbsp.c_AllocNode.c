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
typedef  int /*<<< orphan*/  node_t ;

/* Variables and functions */
 int /*<<< orphan*/ * GetMemory (int) ; 
 scalar_t__ MemorySize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_nodememory ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int numthreads ; 

node_t *AllocNode (void)
{
	node_t	*node;

	node = GetMemory(sizeof(*node));
	memset (node, 0, sizeof(*node));
	if (numthreads == 1)
	{
		c_nodememory += MemorySize(node);
	} //end if
	return node;
}