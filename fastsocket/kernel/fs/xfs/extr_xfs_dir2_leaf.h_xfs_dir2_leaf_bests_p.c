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
struct TYPE_3__ {int /*<<< orphan*/  bestcount; } ;
typedef  TYPE_1__ xfs_dir2_leaf_tail_t ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline __be16 *
xfs_dir2_leaf_bests_p(xfs_dir2_leaf_tail_t *ltp)
{
	return (__be16 *)ltp - be32_to_cpu(ltp->bestcount);
}