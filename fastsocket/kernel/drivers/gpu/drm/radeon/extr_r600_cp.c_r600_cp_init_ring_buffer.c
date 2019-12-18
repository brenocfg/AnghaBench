#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u64 ;
typedef  int u32 ;
struct drm_radeon_master_private {TYPE_7__* sarea_priv; } ;
struct drm_file {TYPE_6__* master; } ;
struct drm_device {TYPE_5__* sg; TYPE_3__* agp; } ;
struct TYPE_19__ {int rptr_update_l2qw; int size_l2qw; scalar_t__ tail; } ;
struct TYPE_25__ {int flags; int gart_vm_start; int gart_size; TYPE_4__* cp_ring; TYPE_2__ ring; TYPE_1__* ring_rptr; } ;
typedef  TYPE_8__ drm_radeon_private_t ;
struct TYPE_24__ {scalar_t__ last_clear; scalar_t__ last_dispatch; scalar_t__ last_frame; } ;
struct TYPE_23__ {struct drm_radeon_master_private* driver_priv; } ;
struct TYPE_22__ {scalar_t__ virtual; } ;
struct TYPE_21__ {unsigned long offset; } ;
struct TYPE_20__ {int base; } ;
struct TYPE_18__ {unsigned long offset; } ;

/* Variables and functions */
 int CHIP_RV770 ; 
 int R600_BUF_SWAP_32BIT ; 
 int /*<<< orphan*/  R600_CP_DEBUG ; 
 int /*<<< orphan*/  R600_CP_ME_CNTL ; 
 int /*<<< orphan*/  R600_CP_RB_BASE ; 
 int /*<<< orphan*/  R600_CP_RB_CNTL ; 
 int /*<<< orphan*/  R600_CP_RB_RPTR_ADDR ; 
 int /*<<< orphan*/  R600_CP_RB_RPTR_ADDR_HI ; 
 int /*<<< orphan*/  R600_CP_RB_RPTR_WR ; 
 int /*<<< orphan*/  R600_CP_RB_WPTR ; 
 int /*<<< orphan*/  R600_CP_RB_WPTR_DELAY ; 
 int /*<<< orphan*/  R600_CP_SEM_WAIT_TIMER ; 
 int /*<<< orphan*/  R600_GRBM_SOFT_RESET ; 
 int /*<<< orphan*/  R600_LAST_CLEAR_REG ; 
 int /*<<< orphan*/  R600_LAST_DISPATCH_REG ; 
 int /*<<< orphan*/  R600_LAST_FRAME_REG ; 
 int R600_RB_NO_UPDATE ; 
 int R600_RB_RPTR_WR_ENA ; 
 int /*<<< orphan*/  R600_SCRATCHOFF (int) ; 
 int /*<<< orphan*/  R600_SCRATCH_ADDR ; 
 scalar_t__ R600_SCRATCH_REG_OFFSET ; 
 int /*<<< orphan*/  R600_SCRATCH_UMSK ; 
 int R600_SOFT_RESET_CP ; 
 int RADEON_BUF_SWAP_32BIT ; 
 int RADEON_FAMILY_MASK ; 
 int RADEON_IS_AGP ; 
 int RADEON_RB_NO_UPDATE ; 
 int RADEON_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RADEON_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_RING_HEAD (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  r600_do_wait_for_idle (TYPE_8__*) ; 
 int /*<<< orphan*/  r600_gfx_init (struct drm_device*,TYPE_8__*) ; 
 int /*<<< orphan*/  r700_gfx_init (struct drm_device*,TYPE_8__*) ; 
 int /*<<< orphan*/  radeon_enable_bm (TYPE_8__*) ; 
 int /*<<< orphan*/  radeon_write_agp_base (TYPE_8__*,int) ; 
 int /*<<< orphan*/  radeon_write_agp_location (TYPE_8__*,int) ; 
 int /*<<< orphan*/  radeon_write_ring_rptr (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void r600_cp_init_ring_buffer(struct drm_device *dev,
				       drm_radeon_private_t *dev_priv,
				       struct drm_file *file_priv)
{
	struct drm_radeon_master_private *master_priv;
	u32 ring_start;
	u64 rptr_addr;

	if (((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_RV770))
		r700_gfx_init(dev, dev_priv);
	else
		r600_gfx_init(dev, dev_priv);

	RADEON_WRITE(R600_GRBM_SOFT_RESET, R600_SOFT_RESET_CP);
	RADEON_READ(R600_GRBM_SOFT_RESET);
	mdelay(15);
	RADEON_WRITE(R600_GRBM_SOFT_RESET, 0);


	/* Set ring buffer size */
#ifdef __BIG_ENDIAN
	RADEON_WRITE(R600_CP_RB_CNTL,
		     R600_BUF_SWAP_32BIT |
		     R600_RB_NO_UPDATE |
		     (dev_priv->ring.rptr_update_l2qw << 8) |
		     dev_priv->ring.size_l2qw);
#else
	RADEON_WRITE(R600_CP_RB_CNTL,
		     RADEON_RB_NO_UPDATE |
		     (dev_priv->ring.rptr_update_l2qw << 8) |
		     dev_priv->ring.size_l2qw);
#endif

	RADEON_WRITE(R600_CP_SEM_WAIT_TIMER, 0x0);

	/* Set the write pointer delay */
	RADEON_WRITE(R600_CP_RB_WPTR_DELAY, 0);

#ifdef __BIG_ENDIAN
	RADEON_WRITE(R600_CP_RB_CNTL,
		     R600_BUF_SWAP_32BIT |
		     R600_RB_NO_UPDATE |
		     R600_RB_RPTR_WR_ENA |
		     (dev_priv->ring.rptr_update_l2qw << 8) |
		     dev_priv->ring.size_l2qw);
#else
	RADEON_WRITE(R600_CP_RB_CNTL,
		     R600_RB_NO_UPDATE |
		     R600_RB_RPTR_WR_ENA |
		     (dev_priv->ring.rptr_update_l2qw << 8) |
		     dev_priv->ring.size_l2qw);
#endif

	/* Initialize the ring buffer's read and write pointers */
	RADEON_WRITE(R600_CP_RB_RPTR_WR, 0);
	RADEON_WRITE(R600_CP_RB_WPTR, 0);
	SET_RING_HEAD(dev_priv, 0);
	dev_priv->ring.tail = 0;

#if __OS_HAS_AGP
	if (dev_priv->flags & RADEON_IS_AGP) {
		rptr_addr = dev_priv->ring_rptr->offset
			- dev->agp->base +
			dev_priv->gart_vm_start;
	} else
#endif
	{
		rptr_addr = dev_priv->ring_rptr->offset
			- ((unsigned long) dev->sg->virtual)
			+ dev_priv->gart_vm_start;
	}
	RADEON_WRITE(R600_CP_RB_RPTR_ADDR, (rptr_addr & 0xfffffffc));
	RADEON_WRITE(R600_CP_RB_RPTR_ADDR_HI, upper_32_bits(rptr_addr));

#ifdef __BIG_ENDIAN
	RADEON_WRITE(R600_CP_RB_CNTL,
		     RADEON_BUF_SWAP_32BIT |
		     (dev_priv->ring.rptr_update_l2qw << 8) |
		     dev_priv->ring.size_l2qw);
#else
	RADEON_WRITE(R600_CP_RB_CNTL,
		     (dev_priv->ring.rptr_update_l2qw << 8) |
		     dev_priv->ring.size_l2qw);
#endif

#if __OS_HAS_AGP
	if (dev_priv->flags & RADEON_IS_AGP) {
		/* XXX */
		radeon_write_agp_base(dev_priv, dev->agp->base);

		/* XXX */
		radeon_write_agp_location(dev_priv,
			     (((dev_priv->gart_vm_start - 1 +
				dev_priv->gart_size) & 0xffff0000) |
			      (dev_priv->gart_vm_start >> 16)));

		ring_start = (dev_priv->cp_ring->offset
			      - dev->agp->base
			      + dev_priv->gart_vm_start);
	} else
#endif
		ring_start = (dev_priv->cp_ring->offset
			      - (unsigned long)dev->sg->virtual
			      + dev_priv->gart_vm_start);

	RADEON_WRITE(R600_CP_RB_BASE, ring_start >> 8);

	RADEON_WRITE(R600_CP_ME_CNTL, 0xff);

	RADEON_WRITE(R600_CP_DEBUG, (1 << 27) | (1 << 28));

	/* Initialize the scratch register pointer.  This will cause
	 * the scratch register values to be written out to memory
	 * whenever they are updated.
	 *
	 * We simply put this behind the ring read pointer, this works
	 * with PCI GART as well as (whatever kind of) AGP GART
	 */
	{
		u64 scratch_addr;

		scratch_addr = RADEON_READ(R600_CP_RB_RPTR_ADDR) & 0xFFFFFFFC;
		scratch_addr |= ((u64)RADEON_READ(R600_CP_RB_RPTR_ADDR_HI)) << 32;
		scratch_addr += R600_SCRATCH_REG_OFFSET;
		scratch_addr >>= 8;
		scratch_addr &= 0xffffffff;

		RADEON_WRITE(R600_SCRATCH_ADDR, (uint32_t)scratch_addr);
	}

	RADEON_WRITE(R600_SCRATCH_UMSK, 0x7);

	/* Turn on bus mastering */
	radeon_enable_bm(dev_priv);

	radeon_write_ring_rptr(dev_priv, R600_SCRATCHOFF(0), 0);
	RADEON_WRITE(R600_LAST_FRAME_REG, 0);

	radeon_write_ring_rptr(dev_priv, R600_SCRATCHOFF(1), 0);
	RADEON_WRITE(R600_LAST_DISPATCH_REG, 0);

	radeon_write_ring_rptr(dev_priv, R600_SCRATCHOFF(2), 0);
	RADEON_WRITE(R600_LAST_CLEAR_REG, 0);

	/* reset sarea copies of these */
	master_priv = file_priv->master->driver_priv;
	if (master_priv->sarea_priv) {
		master_priv->sarea_priv->last_frame = 0;
		master_priv->sarea_priv->last_dispatch = 0;
		master_priv->sarea_priv->last_clear = 0;
	}

	r600_do_wait_for_idle(dev_priv);

}