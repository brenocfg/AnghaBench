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
struct netfs_trans_dst {int /*<<< orphan*/  trans; } ;

/* Variables and functions */
 int /*<<< orphan*/  mempool_free (struct netfs_trans_dst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netfs_trans_dst_pool ; 
 int /*<<< orphan*/  netfs_trans_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void netfs_trans_free_dst(struct netfs_trans_dst *dst)
{
	netfs_trans_put(dst->trans);
	mempool_free(dst, netfs_trans_dst_pool);
}