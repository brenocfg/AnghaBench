#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int flags; scalar_t__ writeback_works; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int CHIP_R600 ; 
 int /*<<< orphan*/  R600_CP_RB_RPTR ; 
 int /*<<< orphan*/  RADEON_CP_RB_RPTR ; 
 int RADEON_FAMILY_MASK ; 
 int /*<<< orphan*/  RADEON_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_read_ring_rptr (TYPE_1__*,int /*<<< orphan*/ ) ; 

u32 radeon_get_ring_head(drm_radeon_private_t *dev_priv)
{
	if (dev_priv->writeback_works)
		return radeon_read_ring_rptr(dev_priv, 0);
	else {
		if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_R600)
			return RADEON_READ(R600_CP_RB_RPTR);
		else
			return RADEON_READ(RADEON_CP_RB_RPTR);
	}
}