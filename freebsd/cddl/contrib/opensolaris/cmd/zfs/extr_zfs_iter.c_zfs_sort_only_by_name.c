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
struct TYPE_3__ {scalar_t__ sc_prop; int /*<<< orphan*/ * sc_next; } ;
typedef  TYPE_1__ zfs_sort_column_t ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ ZFS_PROP_NAME ; 

boolean_t
zfs_sort_only_by_name(const zfs_sort_column_t *sc)
{

	return (sc != NULL && sc->sc_next == NULL &&
	    sc->sc_prop == ZFS_PROP_NAME);
}