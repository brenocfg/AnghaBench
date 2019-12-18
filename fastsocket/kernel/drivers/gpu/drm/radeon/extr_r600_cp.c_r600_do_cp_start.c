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
typedef  int u32 ;
struct TYPE_3__ {int flags; int r600_max_hw_contexts; int cp_running; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int CHIP_RV770 ; 
 int /*<<< orphan*/  COMMIT_RING () ; 
 int CP_PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int /*<<< orphan*/  R600_CP_ME_CNTL ; 
 int /*<<< orphan*/  R600_IT_ME_INITIALIZE ; 
 int R600_ME_INITIALIZE_DEVICE_ID (int) ; 
 int RADEON_FAMILY_MASK ; 
 int /*<<< orphan*/  RADEON_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RING_LOCALS ; 

void r600_do_cp_start(drm_radeon_private_t *dev_priv)
{
	u32 cp_me;
	RING_LOCALS;
	DRM_DEBUG("\n");

	BEGIN_RING(7);
	OUT_RING(CP_PACKET3(R600_IT_ME_INITIALIZE, 5));
	OUT_RING(0x00000001);
	if (((dev_priv->flags & RADEON_FAMILY_MASK) < CHIP_RV770))
		OUT_RING(0x00000003);
	else
		OUT_RING(0x00000000);
	OUT_RING((dev_priv->r600_max_hw_contexts - 1));
	OUT_RING(R600_ME_INITIALIZE_DEVICE_ID(1));
	OUT_RING(0x00000000);
	OUT_RING(0x00000000);
	ADVANCE_RING();
	COMMIT_RING();

	/* set the mux and reset the halt bit */
	cp_me = 0xff;
	RADEON_WRITE(R600_CP_ME_CNTL, cp_me);

	dev_priv->cp_running = 1;

}