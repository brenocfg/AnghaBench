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
struct vxfs_sb_info {int /*<<< orphan*/  vsi_fshino; } ;
struct vxfs_oltfshead {int /*<<< orphan*/ * olt_fsino; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
vxfs_get_fshead(struct vxfs_oltfshead *fshp, struct vxfs_sb_info *infp)
{
	BUG_ON(infp->vsi_fshino);
	infp->vsi_fshino = fshp->olt_fsino[0];
}