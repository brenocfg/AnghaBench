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
 int /*<<< orphan*/  cifs_req_cachep ; 
 int /*<<< orphan*/  cifs_req_poolp ; 
 int /*<<< orphan*/  cifs_sm_req_cachep ; 
 int /*<<< orphan*/  cifs_sm_req_poolp ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cifs_destroy_request_bufs(void)
{
	mempool_destroy(cifs_req_poolp);
	kmem_cache_destroy(cifs_req_cachep);
	mempool_destroy(cifs_sm_req_poolp);
	kmem_cache_destroy(cifs_sm_req_cachep);
}