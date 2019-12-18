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
struct radeon_ring {int dummy; } ;
struct radeon_device {int num_gb_pipes; } ;

/* Variables and functions */
 int PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int R300_BACK_PTYPE_TRIANGE ; 
 int R300_COLOR_ROUND_NEAREST ; 
 int /*<<< orphan*/  R300_DST_PIPE_CONFIG ; 
 unsigned int R300_ENABLE_TILING ; 
 int R300_FRONT_PTYPE_TRIANGE ; 
 int R300_GA_DEADLOCK_CNTL ; 
 int /*<<< orphan*/  R300_GA_ENHANCE ; 
 int R300_GA_FASTSYNC_CNTL ; 
 int /*<<< orphan*/  R300_GA_POLY_MODE ; 
 int /*<<< orphan*/  R300_GA_ROUND_MODE ; 
 int /*<<< orphan*/  R300_GB_AA_CONFIG ; 
 int /*<<< orphan*/  R300_GB_ENABLE ; 
 int /*<<< orphan*/  R300_GB_MSPOS0 ; 
 int /*<<< orphan*/  R300_GB_MSPOS1 ; 
 int /*<<< orphan*/  R300_GB_SELECT ; 
 int /*<<< orphan*/  R300_GB_TILE_CONFIG ; 
 int R300_GEOMETRY_ROUND_NEAREST ; 
 int R300_MSBD0_X_SHIFT ; 
 int R300_MSBD0_Y_SHIFT ; 
 int R300_MSBD1_SHIFT ; 
 int R300_MS_X0_SHIFT ; 
 int R300_MS_X1_SHIFT ; 
 int R300_MS_X2_SHIFT ; 
 int R300_MS_X3_SHIFT ; 
 int R300_MS_X4_SHIFT ; 
 int R300_MS_X5_SHIFT ; 
 int R300_MS_Y0_SHIFT ; 
 int R300_MS_Y1_SHIFT ; 
 int R300_MS_Y2_SHIFT ; 
 int R300_MS_Y3_SHIFT ; 
 int R300_MS_Y4_SHIFT ; 
 int R300_MS_Y5_SHIFT ; 
 int R300_PIPE_AUTO_CONFIG ; 
 unsigned int R300_PIPE_COUNT_R300 ; 
 unsigned int R300_PIPE_COUNT_R420 ; 
 unsigned int R300_PIPE_COUNT_R420_3P ; 
 unsigned int R300_PIPE_COUNT_RV350 ; 
 int R300_RB3D_DC_FLUSH ; 
 int R300_RB3D_DC_FREE ; 
 int /*<<< orphan*/  R300_RB3D_DSTCACHE_CTLSTAT ; 
 int /*<<< orphan*/  R300_RB3D_ZCACHE_CTLSTAT ; 
 unsigned int R300_TILE_SIZE_16 ; 
 int R300_ZC_FLUSH ; 
 int R300_ZC_FREE ; 
 int RADEON_ISYNC_ANY2D_IDLE3D ; 
 int RADEON_ISYNC_ANY3D_IDLE2D ; 
 int /*<<< orphan*/  RADEON_ISYNC_CNTL ; 
 int RADEON_ISYNC_CPSCRATCH_IDLEGUI ; 
 int RADEON_ISYNC_WAIT_IDLEGUI ; 
 int RADEON_WAIT_2D_IDLECLEAN ; 
 int RADEON_WAIT_3D_IDLECLEAN ; 
 int /*<<< orphan*/  RADEON_WAIT_UNTIL ; 
 int radeon_ring_lock (struct radeon_device*,struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_ring_unlock_commit (struct radeon_device*,struct radeon_ring*) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 

void r300_ring_start(struct radeon_device *rdev, struct radeon_ring *ring)
{
	unsigned gb_tile_config;
	int r;

	/* Sub pixel 1/12 so we can have 4K rendering according to doc */
	gb_tile_config = (R300_ENABLE_TILING | R300_TILE_SIZE_16);
	switch(rdev->num_gb_pipes) {
	case 2:
		gb_tile_config |= R300_PIPE_COUNT_R300;
		break;
	case 3:
		gb_tile_config |= R300_PIPE_COUNT_R420_3P;
		break;
	case 4:
		gb_tile_config |= R300_PIPE_COUNT_R420;
		break;
	case 1:
	default:
		gb_tile_config |= R300_PIPE_COUNT_RV350;
		break;
	}

	r = radeon_ring_lock(rdev, ring, 64);
	if (r) {
		return;
	}
	radeon_ring_write(ring, PACKET0(RADEON_ISYNC_CNTL, 0));
	radeon_ring_write(ring,
			  RADEON_ISYNC_ANY2D_IDLE3D |
			  RADEON_ISYNC_ANY3D_IDLE2D |
			  RADEON_ISYNC_WAIT_IDLEGUI |
			  RADEON_ISYNC_CPSCRATCH_IDLEGUI);
	radeon_ring_write(ring, PACKET0(R300_GB_TILE_CONFIG, 0));
	radeon_ring_write(ring, gb_tile_config);
	radeon_ring_write(ring, PACKET0(RADEON_WAIT_UNTIL, 0));
	radeon_ring_write(ring,
			  RADEON_WAIT_2D_IDLECLEAN |
			  RADEON_WAIT_3D_IDLECLEAN);
	radeon_ring_write(ring, PACKET0(R300_DST_PIPE_CONFIG, 0));
	radeon_ring_write(ring, R300_PIPE_AUTO_CONFIG);
	radeon_ring_write(ring, PACKET0(R300_GB_SELECT, 0));
	radeon_ring_write(ring, 0);
	radeon_ring_write(ring, PACKET0(R300_GB_ENABLE, 0));
	radeon_ring_write(ring, 0);
	radeon_ring_write(ring, PACKET0(R300_RB3D_DSTCACHE_CTLSTAT, 0));
	radeon_ring_write(ring, R300_RB3D_DC_FLUSH | R300_RB3D_DC_FREE);
	radeon_ring_write(ring, PACKET0(R300_RB3D_ZCACHE_CTLSTAT, 0));
	radeon_ring_write(ring, R300_ZC_FLUSH | R300_ZC_FREE);
	radeon_ring_write(ring, PACKET0(RADEON_WAIT_UNTIL, 0));
	radeon_ring_write(ring,
			  RADEON_WAIT_2D_IDLECLEAN |
			  RADEON_WAIT_3D_IDLECLEAN);
	radeon_ring_write(ring, PACKET0(R300_GB_AA_CONFIG, 0));
	radeon_ring_write(ring, 0);
	radeon_ring_write(ring, PACKET0(R300_RB3D_DSTCACHE_CTLSTAT, 0));
	radeon_ring_write(ring, R300_RB3D_DC_FLUSH | R300_RB3D_DC_FREE);
	radeon_ring_write(ring, PACKET0(R300_RB3D_ZCACHE_CTLSTAT, 0));
	radeon_ring_write(ring, R300_ZC_FLUSH | R300_ZC_FREE);
	radeon_ring_write(ring, PACKET0(R300_GB_MSPOS0, 0));
	radeon_ring_write(ring,
			  ((6 << R300_MS_X0_SHIFT) |
			   (6 << R300_MS_Y0_SHIFT) |
			   (6 << R300_MS_X1_SHIFT) |
			   (6 << R300_MS_Y1_SHIFT) |
			   (6 << R300_MS_X2_SHIFT) |
			   (6 << R300_MS_Y2_SHIFT) |
			   (6 << R300_MSBD0_Y_SHIFT) |
			   (6 << R300_MSBD0_X_SHIFT)));
	radeon_ring_write(ring, PACKET0(R300_GB_MSPOS1, 0));
	radeon_ring_write(ring,
			  ((6 << R300_MS_X3_SHIFT) |
			   (6 << R300_MS_Y3_SHIFT) |
			   (6 << R300_MS_X4_SHIFT) |
			   (6 << R300_MS_Y4_SHIFT) |
			   (6 << R300_MS_X5_SHIFT) |
			   (6 << R300_MS_Y5_SHIFT) |
			   (6 << R300_MSBD1_SHIFT)));
	radeon_ring_write(ring, PACKET0(R300_GA_ENHANCE, 0));
	radeon_ring_write(ring, R300_GA_DEADLOCK_CNTL | R300_GA_FASTSYNC_CNTL);
	radeon_ring_write(ring, PACKET0(R300_GA_POLY_MODE, 0));
	radeon_ring_write(ring,
			  R300_FRONT_PTYPE_TRIANGE | R300_BACK_PTYPE_TRIANGE);
	radeon_ring_write(ring, PACKET0(R300_GA_ROUND_MODE, 0));
	radeon_ring_write(ring,
			  R300_GEOMETRY_ROUND_NEAREST |
			  R300_COLOR_ROUND_NEAREST);
	radeon_ring_unlock_commit(rdev, ring);
}