#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  zpool_config; } ;
typedef  TYPE_1__ zpool_handle_t ;

/* Variables and functions */
 int zpool_get_config_physpath (int /*<<< orphan*/ ,char*,size_t) ; 

int
zpool_get_physpath(zpool_handle_t *zhp, char *physpath, size_t phypath_size)
{
	return (zpool_get_config_physpath(zhp->zpool_config, physpath,
	    phypath_size));
}