#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ i8count; } ;
struct TYPE_5__ {TYPE_1__ hdr; } ;
typedef  TYPE_2__ xfs_dir2_sf_t ;
typedef  int /*<<< orphan*/  xfs_dir2_sf_entry_t ;
typedef  int /*<<< orphan*/  xfs_dir2_ino8_t ;
typedef  int /*<<< orphan*/  xfs_dir2_ino4_t ;
typedef  int uint ;
typedef  int len ;

/* Variables and functions */

__attribute__((used)) static inline int xfs_dir2_sf_entsize_byname(xfs_dir2_sf_t *sfp, int len)
{
	return ((uint)sizeof(xfs_dir2_sf_entry_t) - 1 + (len) - \
		((sfp)->hdr.i8count == 0) * \
		((uint)sizeof(xfs_dir2_ino8_t) - (uint)sizeof(xfs_dir2_ino4_t)));
}