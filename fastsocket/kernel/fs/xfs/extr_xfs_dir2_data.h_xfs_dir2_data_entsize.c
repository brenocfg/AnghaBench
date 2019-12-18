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
typedef  int /*<<< orphan*/  xfs_dir2_data_off_t ;
typedef  scalar_t__ uint ;
typedef  scalar_t__ n ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_DIR2_DATA_ALIGN ; 
 int /*<<< orphan*/ * name ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ roundup (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_data_entry_t ; 

__attribute__((used)) static inline int xfs_dir2_data_entsize(int n)
{
	return (int)roundup(offsetof(xfs_dir2_data_entry_t, name[0]) + (n) + \
		 (uint)sizeof(xfs_dir2_data_off_t), XFS_DIR2_DATA_ALIGN);
}