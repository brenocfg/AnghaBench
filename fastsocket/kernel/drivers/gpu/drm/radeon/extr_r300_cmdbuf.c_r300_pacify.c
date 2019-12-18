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
typedef  int uint32_t ;
struct TYPE_3__ {int track_flush; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int CP_PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int /*<<< orphan*/  R300_DSTCACHE_CTLSTAT ; 
 int R300_RB2D_DC_FLUSH ; 
 int R300_RB2D_DC_FREE ; 
 int /*<<< orphan*/  R300_RB3D_AARESOLVE_CTL ; 
 int R300_RB3D_DC_FLUSH ; 
 int R300_RB3D_DC_FREE ; 
 int /*<<< orphan*/  R300_RB3D_DSTCACHE_CTLSTAT ; 
 int /*<<< orphan*/  R300_TX_INVALTAGS ; 
 int /*<<< orphan*/  R300_ZB_ZCACHE_CTLSTAT ; 
 int R300_ZC_FLUSH ; 
 int R300_ZC_FREE ; 
 int RADEON_FLUSH_EMITED ; 
 int RADEON_PURGE_EMITED ; 
 int RADEON_WAIT_2D_IDLECLEAN ; 
 int RADEON_WAIT_3D_IDLECLEAN ; 
 int RADEON_WAIT_HOST_IDLECLEAN ; 
 int /*<<< orphan*/  RADEON_WAIT_UNTIL ; 
 int /*<<< orphan*/  RING_LOCALS ; 

__attribute__((used)) static void r300_pacify(drm_radeon_private_t *dev_priv)
{
	uint32_t cache_z, cache_3d, cache_2d;
	RING_LOCALS;

	cache_z = R300_ZC_FLUSH;
	cache_2d = R300_RB2D_DC_FLUSH;
	cache_3d = R300_RB3D_DC_FLUSH;
	if (!(dev_priv->track_flush & RADEON_PURGE_EMITED)) {
		/* we can purge, primitive where draw since last purge */
		cache_z |= R300_ZC_FREE;
		cache_2d |= R300_RB2D_DC_FREE;
		cache_3d |= R300_RB3D_DC_FREE;
	}

	/* flush & purge zbuffer */
	BEGIN_RING(2);
	OUT_RING(CP_PACKET0(R300_ZB_ZCACHE_CTLSTAT, 0));
	OUT_RING(cache_z);
	ADVANCE_RING();
	/* flush & purge 3d */
	BEGIN_RING(2);
	OUT_RING(CP_PACKET0(R300_RB3D_DSTCACHE_CTLSTAT, 0));
	OUT_RING(cache_3d);
	ADVANCE_RING();
	/* flush & purge texture */
	BEGIN_RING(2);
	OUT_RING(CP_PACKET0(R300_TX_INVALTAGS, 0));
	OUT_RING(0);
	ADVANCE_RING();
	/* FIXME: is this one really needed ? */
	BEGIN_RING(2);
	OUT_RING(CP_PACKET0(R300_RB3D_AARESOLVE_CTL, 0));
	OUT_RING(0);
	ADVANCE_RING();
	BEGIN_RING(2);
	OUT_RING(CP_PACKET0(RADEON_WAIT_UNTIL, 0));
	OUT_RING(RADEON_WAIT_3D_IDLECLEAN);
	ADVANCE_RING();
	/* flush & purge 2d through E2 as RB2D will trigger lockup */
	BEGIN_RING(4);
	OUT_RING(CP_PACKET0(R300_DSTCACHE_CTLSTAT, 0));
	OUT_RING(cache_2d);
	OUT_RING(CP_PACKET0(RADEON_WAIT_UNTIL, 0));
	OUT_RING(RADEON_WAIT_2D_IDLECLEAN |
		 RADEON_WAIT_HOST_IDLECLEAN);
	ADVANCE_RING();
	/* set flush & purge flags */
	dev_priv->track_flush |= RADEON_FLUSH_EMITED | RADEON_PURGE_EMITED;
}