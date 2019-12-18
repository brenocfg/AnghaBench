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
struct TYPE_4__ {int /*<<< orphan*/  i; } ;
struct TYPE_5__ {TYPE_1__ offset; } ;
typedef  TYPE_2__ xfs_dir2_sf_entry_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_aoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  INT_GET_UNALIGNED_16_BE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline xfs_dir2_data_aoff_t
xfs_dir2_sf_get_offset(xfs_dir2_sf_entry_t *sfep)
{
	return INT_GET_UNALIGNED_16_BE(&(sfep)->offset.i);
}