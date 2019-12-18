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
struct TYPE_5__ {TYPE_1__* entries; } ;
typedef  TYPE_2__ xfs_attr_leafblock_t ;
typedef  int /*<<< orphan*/  xfs_attr_leaf_name_local_t ;
struct TYPE_4__ {int /*<<< orphan*/  nameidx; } ;

/* Variables and functions */
 size_t be16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline xfs_attr_leaf_name_local_t *
xfs_attr_leaf_name_local(xfs_attr_leafblock_t *leafp, int idx)
{
	return (xfs_attr_leaf_name_local_t *)
		&((char *)leafp)[be16_to_cpu(leafp->entries[idx].nameidx)];
}