#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_ino_t ;
struct TYPE_6__ {scalar_t__ i8count; } ;
struct TYPE_7__ {TYPE_1__ hdr; } ;
typedef  TYPE_2__ xfs_dir2_sf_t ;
struct TYPE_8__ {int /*<<< orphan*/  i8; int /*<<< orphan*/  i4; } ;
typedef  TYPE_3__ xfs_dir2_inou_t ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_PUT_DIR_INO4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_PUT_DIR_INO8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void xfs_dir2_sf_put_inumber(xfs_dir2_sf_t *sfp, xfs_ino_t *from,
						xfs_dir2_inou_t *to)
{
	if ((sfp)->hdr.i8count == 0)
		XFS_PUT_DIR_INO4(*(from), (to)->i4);
	else
		XFS_PUT_DIR_INO8(*(from), (to)->i8);
}