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
struct TYPE_3__ {scalar_t__* cb_columns; } ;
typedef  TYPE_1__ zprop_get_cbdata_t ;
typedef  scalar_t__ zfs_get_column_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ GET_COL_NONE ; 
 scalar_t__ GET_COL_RECVD ; 
 int ZFS_GET_NCOLS ; 

__attribute__((used)) static boolean_t
is_recvd_column(zprop_get_cbdata_t *cbp)
{
	int i;
	zfs_get_column_t col;

	for (i = 0; i < ZFS_GET_NCOLS &&
	    (col = cbp->cb_columns[i]) != GET_COL_NONE; i++)
		if (col == GET_COL_RECVD)
			return (B_TRUE);
	return (B_FALSE);
}