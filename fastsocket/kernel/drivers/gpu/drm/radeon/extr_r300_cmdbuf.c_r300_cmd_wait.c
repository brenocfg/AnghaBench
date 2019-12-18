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
typedef  int u32 ;
typedef  int /*<<< orphan*/  drm_radeon_private_t ;
struct TYPE_4__ {int flags; } ;
struct TYPE_5__ {TYPE_1__ wait; } ;
typedef  TYPE_2__ drm_r300_cmd_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int CP_PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
#define  R300_NEW_WAIT_2D_2D_CLEAN 133 
#define  R300_NEW_WAIT_2D_2D_CLEAN_3D_3D_CLEAN 132 
#define  R300_NEW_WAIT_2D_3D 131 
#define  R300_NEW_WAIT_3D_3D_CLEAN 130 
#define  R300_WAIT_2D 129 
#define  R300_WAIT_3D 128 
 int RADEON_WAIT_2D_IDLE ; 
 int RADEON_WAIT_2D_IDLECLEAN ; 
 int RADEON_WAIT_3D_IDLE ; 
 int RADEON_WAIT_3D_IDLECLEAN ; 
 int /*<<< orphan*/  RADEON_WAIT_UNTIL ; 
 int /*<<< orphan*/  RING_LOCALS ; 

__attribute__((used)) static void r300_cmd_wait(drm_radeon_private_t * dev_priv,
			  drm_r300_cmd_header_t header)
{
	u32 wait_until;
	RING_LOCALS;

	if (!header.wait.flags)
		return;

	wait_until = 0;

	switch(header.wait.flags) {
	case R300_WAIT_2D:
		wait_until = RADEON_WAIT_2D_IDLE;
		break;
	case R300_WAIT_3D:
		wait_until = RADEON_WAIT_3D_IDLE;
		break;
	case R300_NEW_WAIT_2D_3D:
		wait_until = RADEON_WAIT_2D_IDLE|RADEON_WAIT_3D_IDLE;
		break;
	case R300_NEW_WAIT_2D_2D_CLEAN:
		wait_until = RADEON_WAIT_2D_IDLE|RADEON_WAIT_2D_IDLECLEAN;
		break;
	case R300_NEW_WAIT_3D_3D_CLEAN:
		wait_until = RADEON_WAIT_3D_IDLE|RADEON_WAIT_3D_IDLECLEAN;
		break;
	case R300_NEW_WAIT_2D_2D_CLEAN_3D_3D_CLEAN:
		wait_until = RADEON_WAIT_2D_IDLE|RADEON_WAIT_2D_IDLECLEAN;
		wait_until |= RADEON_WAIT_3D_IDLE|RADEON_WAIT_3D_IDLECLEAN;
		break;
	default:
		return;
	}

	BEGIN_RING(2);
	OUT_RING(CP_PACKET0(RADEON_WAIT_UNTIL, 0));
	OUT_RING(wait_until);
	ADVANCE_RING();
}