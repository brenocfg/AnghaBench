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
typedef  int /*<<< orphan*/  xfs_dir2_sf_t ;
typedef  int /*<<< orphan*/  xfs_dir2_sf_entry_t ;
typedef  scalar_t__ sfep ;

/* Variables and functions */
 scalar_t__ xfs_dir2_sf_entsize_byentry (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline xfs_dir2_sf_entry_t *
xfs_dir2_sf_nextentry(xfs_dir2_sf_t *sfp, xfs_dir2_sf_entry_t *sfep)
{
	return ((xfs_dir2_sf_entry_t *) \
		((char *)(sfep) + xfs_dir2_sf_entsize_byentry(sfp,sfep)));
}