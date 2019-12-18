#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct drm_radeon_master_private {TYPE_7__* sarea_priv; } ;
struct drm_file {TYPE_6__* master; } ;
struct drm_device {TYPE_4__* sg; TYPE_2__* agp; } ;
struct TYPE_21__ {int tail; int fetch_size_l2ow; int rptr_update_l2qw; int size_l2qw; } ;
struct TYPE_24__ {int gart_vm_start; int fb_location; int flags; int gart_size; TYPE_5__ ring; TYPE_3__* ring_rptr; TYPE_1__* cp_ring; int /*<<< orphan*/  new_memmap; } ;
typedef  TYPE_8__ drm_radeon_private_t ;
struct TYPE_23__ {scalar_t__ last_clear; scalar_t__ last_dispatch; scalar_t__ last_frame; } ;
struct TYPE_22__ {struct drm_radeon_master_private* driver_priv; } ;
struct TYPE_20__ {scalar_t__ virtual; } ;
struct TYPE_19__ {unsigned long offset; } ;
struct TYPE_18__ {int base; } ;
struct TYPE_17__ {unsigned long offset; } ;

/* Variables and functions */
 int RADEON_BUF_SWAP_32BIT ; 
 int /*<<< orphan*/  RADEON_CP_RB_BASE ; 
 int /*<<< orphan*/  RADEON_CP_RB_CNTL ; 
 int /*<<< orphan*/  RADEON_CP_RB_RPTR ; 
 int /*<<< orphan*/  RADEON_CP_RB_RPTR_ADDR ; 
 int /*<<< orphan*/  RADEON_CP_RB_WPTR ; 
 int /*<<< orphan*/  RADEON_CP_RB_WPTR_DELAY ; 
 int RADEON_ISYNC_ANY2D_IDLE3D ; 
 int RADEON_ISYNC_ANY3D_IDLE2D ; 
 int /*<<< orphan*/  RADEON_ISYNC_CNTL ; 
 int RADEON_ISYNC_CPSCRATCH_IDLEGUI ; 
 int RADEON_ISYNC_WAIT_IDLEGUI ; 
 int RADEON_IS_AGP ; 
 int /*<<< orphan*/  RADEON_LAST_CLEAR_REG ; 
 int /*<<< orphan*/  RADEON_LAST_DISPATCH_REG ; 
 int /*<<< orphan*/  RADEON_LAST_FRAME_REG ; 
 int RADEON_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RADEON_SCRATCHOFF (int) ; 
 int /*<<< orphan*/  RADEON_SCRATCH_ADDR ; 
 int RADEON_SCRATCH_REG_OFFSET ; 
 int /*<<< orphan*/  RADEON_SCRATCH_UMSK ; 
 int /*<<< orphan*/  RADEON_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_RING_HEAD (TYPE_8__*,int) ; 
 int /*<<< orphan*/  radeon_do_wait_for_idle (TYPE_8__*) ; 
 int /*<<< orphan*/  radeon_enable_bm (TYPE_8__*) ; 
 int /*<<< orphan*/  radeon_write_agp_base (TYPE_8__*,int) ; 
 int /*<<< orphan*/  radeon_write_agp_location (TYPE_8__*,int) ; 
 int /*<<< orphan*/  radeon_write_fb_location (TYPE_8__*,int) ; 
 int /*<<< orphan*/  radeon_write_ring_rptr (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void radeon_cp_init_ring_buffer(struct drm_device * dev,
				       drm_radeon_private_t *dev_priv,
				       struct drm_file *file_priv)
{
	struct drm_radeon_master_private *master_priv;
	u32 ring_start, cur_read_ptr;

	/* Initialize the memory controller. With new memory map, the fb location
	 * is not changed, it should have been properly initialized already. Part
	 * of the problem is that the code below is bogus, assuming the GART is
	 * always appended to the fb which is not necessarily the case
	 */
	if (!dev_priv->new_memmap)
		radeon_write_fb_location(dev_priv,
			     ((dev_priv->gart_vm_start - 1) & 0xffff0000)
			     | (dev_priv->fb_location >> 16));

#if __OS_HAS_AGP
	if (dev_priv->flags & RADEON_IS_AGP) {
		radeon_write_agp_base(dev_priv, dev->agp->base);

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

	RADEON_WRITE(RADEON_CP_RB_BASE, ring_start);

	/* Set the write pointer delay */
	RADEON_WRITE(RADEON_CP_RB_WPTR_DELAY, 0);

	/* Initialize the ring buffer's read and write pointers */
	cur_read_ptr = RADEON_READ(RADEON_CP_RB_RPTR);
	RADEON_WRITE(RADEON_CP_RB_WPTR, cur_read_ptr);
	SET_RING_HEAD(dev_priv, cur_read_ptr);
	dev_priv->ring.tail = cur_read_ptr;

#if __OS_HAS_AGP
	if (dev_priv->flags & RADEON_IS_AGP) {
		RADEON_WRITE(RADEON_CP_RB_RPTR_ADDR,
			     dev_priv->ring_rptr->offset
			     - dev->agp->base + dev_priv->gart_vm_start);
	} else
#endif
	{
		RADEON_WRITE(RADEON_CP_RB_RPTR_ADDR,
			     dev_priv->ring_rptr->offset
			     - ((unsigned long) dev->sg->virtual)
			     + dev_priv->gart_vm_start);
	}

	/* Set ring buffer size */
#ifdef __BIG_ENDIAN
	RADEON_WRITE(RADEON_CP_RB_CNTL,
		     RADEON_BUF_SWAP_32BIT |
		     (dev_priv->ring.fetch_size_l2ow << 18) |
		     (dev_priv->ring.rptr_update_l2qw << 8) |
		     dev_priv->ring.size_l2qw);
#else
	RADEON_WRITE(RADEON_CP_RB_CNTL,
		     (dev_priv->ring.fetch_size_l2ow << 18) |
		     (dev_priv->ring.rptr_update_l2qw << 8) |
		     dev_priv->ring.size_l2qw);
#endif


	/* Initialize the scratch register pointer.  This will cause
	 * the scratch register values to be written out to memory
	 * whenever they are updated.
	 *
	 * We simply put this behind the ring read pointer, this works
	 * with PCI GART as well as (whatever kind of) AGP GART
	 */
	RADEON_WRITE(RADEON_SCRATCH_ADDR, RADEON_READ(RADEON_CP_RB_RPTR_ADDR)
		     + RADEON_SCRATCH_REG_OFFSET);

	RADEON_WRITE(RADEON_SCRATCH_UMSK, 0x7);

	radeon_enable_bm(dev_priv);

	radeon_write_ring_rptr(dev_priv, RADEON_SCRATCHOFF(0), 0);
	RADEON_WRITE(RADEON_LAST_FRAME_REG, 0);

	radeon_write_ring_rptr(dev_priv, RADEON_SCRATCHOFF(1), 0);
	RADEON_WRITE(RADEON_LAST_DISPATCH_REG, 0);

	radeon_write_ring_rptr(dev_priv, RADEON_SCRATCHOFF(2), 0);
	RADEON_WRITE(RADEON_LAST_CLEAR_REG, 0);

	/* reset sarea copies of these */
	master_priv = file_priv->master->driver_priv;
	if (master_priv->sarea_priv) {
		master_priv->sarea_priv->last_frame = 0;
		master_priv->sarea_priv->last_dispatch = 0;
		master_priv->sarea_priv->last_clear = 0;
	}

	radeon_do_wait_for_idle(dev_priv);

	/* Sync everything up */
	RADEON_WRITE(RADEON_ISYNC_CNTL,
		     (RADEON_ISYNC_ANY2D_IDLE3D |
		      RADEON_ISYNC_ANY3D_IDLE2D |
		      RADEON_ISYNC_WAIT_IDLEGUI |
		      RADEON_ISYNC_CPSCRATCH_IDLEGUI));

}