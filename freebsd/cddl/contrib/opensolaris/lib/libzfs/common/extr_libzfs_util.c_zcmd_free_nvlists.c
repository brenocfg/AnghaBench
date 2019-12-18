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
struct TYPE_3__ {int /*<<< orphan*/ * zc_nvlist_dst; int /*<<< orphan*/ * zc_nvlist_src; int /*<<< orphan*/ * zc_nvlist_conf; } ;
typedef  TYPE_1__ zfs_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 

void
zcmd_free_nvlists(zfs_cmd_t *zc)
{
	free((void *)(uintptr_t)zc->zc_nvlist_conf);
	free((void *)(uintptr_t)zc->zc_nvlist_src);
	free((void *)(uintptr_t)zc->zc_nvlist_dst);
	zc->zc_nvlist_conf = NULL;
	zc->zc_nvlist_src = NULL;
	zc->zc_nvlist_dst = NULL;
}