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
typedef  int /*<<< orphan*/  nfsnode_t ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_node_lock_internal (int /*<<< orphan*/ ,int) ; 

void
nfs_node_lock_force(nfsnode_t np)
{
	nfs_node_lock_internal(np, 1);
}