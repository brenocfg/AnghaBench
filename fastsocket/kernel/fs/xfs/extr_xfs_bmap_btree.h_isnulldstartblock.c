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
typedef  int /*<<< orphan*/  xfs_dfsbno_t ;
typedef  scalar_t__ x ;

/* Variables and functions */
 scalar_t__ DSTARTBLOCKMASK ; 

__attribute__((used)) static inline int isnulldstartblock(xfs_dfsbno_t x)
{
	return ((x) & DSTARTBLOCKMASK) == DSTARTBLOCKMASK;
}