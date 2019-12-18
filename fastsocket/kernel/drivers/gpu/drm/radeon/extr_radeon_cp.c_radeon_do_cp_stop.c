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
struct TYPE_4__ {int flags; scalar_t__ cp_running; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int CHIP_R420 ; 
 int /*<<< orphan*/  COMMIT_RING () ; 
 int /*<<< orphan*/  CP_PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  OUT_RING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R300_RB3D_DC_FINISH ; 
 int /*<<< orphan*/  R300_RB3D_DSTCACHE_CTLSTAT ; 
 int /*<<< orphan*/  RADEON_CP_CSQ_CNTL ; 
 int /*<<< orphan*/  RADEON_CSQ_PRIDIS_INDDIS ; 
 int RADEON_FAMILY_MASK ; 
 int /*<<< orphan*/  RADEON_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int /*<<< orphan*/  radeon_do_wait_for_idle (TYPE_1__*) ; 

__attribute__((used)) static void radeon_do_cp_stop(drm_radeon_private_t * dev_priv)
{
	RING_LOCALS;
	DRM_DEBUG("\n");

	/* finish the pending CP_RESYNC token */
	if ((dev_priv->flags & RADEON_FAMILY_MASK) == CHIP_R420) {
		BEGIN_RING(2);
		OUT_RING(CP_PACKET0(R300_RB3D_DSTCACHE_CTLSTAT, 0));
		OUT_RING(R300_RB3D_DC_FINISH);
		ADVANCE_RING();
		COMMIT_RING();
		radeon_do_wait_for_idle(dev_priv);
	}

	RADEON_WRITE(RADEON_CP_CSQ_CNTL, RADEON_CSQ_PRIDIS_INDDIS);

	dev_priv->cp_running = 0;
}