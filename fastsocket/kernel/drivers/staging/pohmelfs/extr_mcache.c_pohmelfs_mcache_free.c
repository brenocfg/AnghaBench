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
struct pohmelfs_sb {int dummy; } ;
struct pohmelfs_mcache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mempool_free (struct pohmelfs_mcache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pohmelfs_mcache_pool ; 
 int /*<<< orphan*/  pohmelfs_mcache_remove_locked (struct pohmelfs_sb*,struct pohmelfs_mcache*) ; 

void pohmelfs_mcache_free(struct pohmelfs_sb *psb, struct pohmelfs_mcache *m)
{
	pohmelfs_mcache_remove_locked(psb, m);

	mempool_free(m, pohmelfs_mcache_pool);
}