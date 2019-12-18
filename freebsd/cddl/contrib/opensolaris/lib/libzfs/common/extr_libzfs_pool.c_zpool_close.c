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
struct TYPE_4__ {int /*<<< orphan*/  zpool_props; int /*<<< orphan*/  zpool_old_config; int /*<<< orphan*/  zpool_config; } ;
typedef  TYPE_1__ zpool_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ ) ; 

void
zpool_close(zpool_handle_t *zhp)
{
	nvlist_free(zhp->zpool_config);
	nvlist_free(zhp->zpool_old_config);
	nvlist_free(zhp->zpool_props);
	free(zhp);
}