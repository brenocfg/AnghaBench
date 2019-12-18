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
typedef  int /*<<< orphan*/  xfs_mru_cache_elem_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  kmem_zone_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_zone_init (int,char*) ; 
 int /*<<< orphan*/  xfs_mru_elem_zone ; 
 int /*<<< orphan*/  xfs_mru_reap_wq ; 

int
xfs_mru_cache_init(void)
{
	xfs_mru_elem_zone = kmem_zone_init(sizeof(xfs_mru_cache_elem_t),
	                                 "xfs_mru_cache_elem");
	if (!xfs_mru_elem_zone)
		goto out;

	xfs_mru_reap_wq = create_singlethread_workqueue("xfs_mru_cache");
	if (!xfs_mru_reap_wq)
		goto out_destroy_mru_elem_zone;

	return 0;

 out_destroy_mru_elem_zone:
	kmem_zone_destroy(xfs_mru_elem_zone);
 out:
	return -ENOMEM;
}