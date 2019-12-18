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

/* Variables and functions */
 int /*<<< orphan*/  L2X0_INV_WAY ; 
 int /*<<< orphan*/  cache_sync () ; 
 int /*<<< orphan*/  sync_writel (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void l2x0_inv_all(void)
{
	/* invalidate all ways */
	sync_writel(0xff, L2X0_INV_WAY, 0xff);
	cache_sync();
}