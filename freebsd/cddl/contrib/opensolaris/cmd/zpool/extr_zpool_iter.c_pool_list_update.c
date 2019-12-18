#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ zl_findall; } ;
typedef  TYPE_1__ zpool_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_pool ; 
 int /*<<< orphan*/  g_zfs ; 
 int /*<<< orphan*/  zpool_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

void
pool_list_update(zpool_list_t *zlp)
{
	if (zlp->zl_findall)
		(void) zpool_iter(g_zfs, add_pool, zlp);
}