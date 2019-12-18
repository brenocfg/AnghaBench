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
typedef  int /*<<< orphan*/  xfs_dir2_db_t ;
typedef  int /*<<< orphan*/  xfs_dir2_dataptr_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_aoff_t ;
struct xfs_mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfs_dir2_byte_to_dataptr (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_db_off_to_byte (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline xfs_dir2_dataptr_t
xfs_dir2_db_off_to_dataptr(struct xfs_mount *mp, xfs_dir2_db_t db,
			   xfs_dir2_data_aoff_t o)
{
	return xfs_dir2_byte_to_dataptr(mp, xfs_dir2_db_off_to_byte(mp, db, o));
}