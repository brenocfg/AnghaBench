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

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_inode_cachep ; 
 int /*<<< orphan*/  rpc_pipe_fs_type ; 
 int /*<<< orphan*/  unregister_filesystem (int /*<<< orphan*/ *) ; 

void unregister_rpc_pipefs(void)
{
	kmem_cache_destroy(rpc_inode_cachep);
	unregister_filesystem(&rpc_pipe_fs_type);
}