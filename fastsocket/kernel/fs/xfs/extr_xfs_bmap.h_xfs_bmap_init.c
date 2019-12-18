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
typedef  int /*<<< orphan*/  xfs_fsblock_t ;
struct TYPE_3__ {scalar_t__ xbf_low; scalar_t__ xbf_count; int /*<<< orphan*/ * xbf_first; } ;
typedef  TYPE_1__ xfs_bmap_free_t ;

/* Variables and functions */
 int /*<<< orphan*/  NULLFSBLOCK ; 

__attribute__((used)) static inline void xfs_bmap_init(xfs_bmap_free_t *flp, xfs_fsblock_t *fbp)
{
	((flp)->xbf_first = NULL, (flp)->xbf_count = 0, \
		(flp)->xbf_low = 0, *(fbp) = NULLFSBLOCK);
}