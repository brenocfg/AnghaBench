#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_5__ {int writeback_works; scalar_t__ usec_timeout; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,...) ; 
 int /*<<< orphan*/  DRM_UDELAY (int) ; 
 int R600_BUF_SWAP_32BIT ; 
 int /*<<< orphan*/  R600_CP_RB_CNTL ; 
 int R600_RB_NO_UPDATE ; 
 int /*<<< orphan*/  R600_SCRATCHOFF (int) ; 
 int /*<<< orphan*/  R600_SCRATCH_REG1 ; 
 int /*<<< orphan*/  R600_SCRATCH_UMSK ; 
 int RADEON_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RADEON_WRITE (int /*<<< orphan*/ ,int) ; 
 int radeon_no_wb ; 
 scalar_t__ radeon_read_ring_rptr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_write_ring_rptr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r600_test_writeback(drm_radeon_private_t *dev_priv)
{
	u32 tmp;

	/* Start with assuming that writeback doesn't work */
	dev_priv->writeback_works = 0;

	/* Writeback doesn't seem to work everywhere, test it here and possibly
	 * enable it if it appears to work
	 */
	radeon_write_ring_rptr(dev_priv, R600_SCRATCHOFF(1), 0);

	RADEON_WRITE(R600_SCRATCH_REG1, 0xdeadbeef);

	for (tmp = 0; tmp < dev_priv->usec_timeout; tmp++) {
		u32 val;

		val = radeon_read_ring_rptr(dev_priv, R600_SCRATCHOFF(1));
		if (val == 0xdeadbeef)
			break;
		DRM_UDELAY(1);
	}

	if (tmp < dev_priv->usec_timeout) {
		dev_priv->writeback_works = 1;
		DRM_INFO("writeback test succeeded in %d usecs\n", tmp);
	} else {
		dev_priv->writeback_works = 0;
		DRM_INFO("writeback test failed\n");
	}
	if (radeon_no_wb == 1) {
		dev_priv->writeback_works = 0;
		DRM_INFO("writeback forced off\n");
	}

	if (!dev_priv->writeback_works) {
		/* Disable writeback to avoid unnecessary bus master transfer */
		RADEON_WRITE(R600_CP_RB_CNTL,
#ifdef __BIG_ENDIAN
			     R600_BUF_SWAP_32BIT |
#endif
			     RADEON_READ(R600_CP_RB_CNTL) |
			     R600_RB_NO_UPDATE);
		RADEON_WRITE(R600_SCRATCH_UMSK, 0);
	}
}