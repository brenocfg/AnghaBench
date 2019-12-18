#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_15__ ;

/* Type definitions */
typedef  int u32 ;
struct drm_radeon_master_private {int /*<<< orphan*/  sarea; } ;
struct drm_file {TYPE_1__* master; } ;
struct drm_device {TYPE_3__* sg; TYPE_15__* agp_buffer_map; TYPE_2__* agp; int /*<<< orphan*/  agp_buffer_token; TYPE_6__* dev_private; } ;
struct TYPE_16__ {unsigned int handle; unsigned long offset; int /*<<< orphan*/  size; } ;
struct TYPE_21__ {unsigned int bus_addr; unsigned int addr; TYPE_15__ mapping; int /*<<< orphan*/  table_size; int /*<<< orphan*/  table_mask; } ;
struct TYPE_20__ {int* start; int* end; int size; int rptr_update; int fetch_size; int tail_mask; int /*<<< orphan*/  high_mark; void* fetch_size_l2ow; void* rptr_update_l2qw; void* size_l2qw; } ;
struct TYPE_22__ {int flags; int usec_timeout; scalar_t__ cp_mode; int front_offset; int front_pitch; int back_offset; int back_pitch; int fb_location; int fb_size; int front_pitch_offset; int back_pitch_offset; int depth_pitch_offset; int depth_pitch; int depth_offset; int gart_size; int gart_vm_start; unsigned long gart_buffers_offset; unsigned int pcigart_offset; int fb_aper_offset; scalar_t__ last_buf; int /*<<< orphan*/  pfp_fw; int /*<<< orphan*/  me_fw; TYPE_5__ gart_info; int /*<<< orphan*/  pcigart_offset_set; TYPE_4__ ring; TYPE_15__* cp_ring; scalar_t__ new_memmap; TYPE_15__* ring_rptr; void* gart_textures; int /*<<< orphan*/  gart_textures_offset; int /*<<< orphan*/  buffers_offset; int /*<<< orphan*/  ring_rptr_offset; int /*<<< orphan*/  ring_offset; int /*<<< orphan*/  color_fmt; scalar_t__ do_boxes; int /*<<< orphan*/  vblank_crtc; int /*<<< orphan*/  cs_mutex; } ;
typedef  TYPE_6__ drm_radeon_private_t ;
struct TYPE_23__ {int usec_timeout; scalar_t__ cp_mode; int fb_bpp; int front_offset; int front_pitch; int back_offset; int back_pitch; int gart_size; int ring_size; int /*<<< orphan*/  gart_textures_offset; int /*<<< orphan*/  buffers_offset; int /*<<< orphan*/  ring_rptr_offset; int /*<<< orphan*/  ring_offset; scalar_t__ is_pci; } ;
typedef  TYPE_7__ drm_radeon_init_t ;
struct TYPE_19__ {scalar_t__ virtual; } ;
struct TYPE_18__ {int base; } ;
struct TYPE_17__ {struct drm_radeon_master_private* driver_priv; } ;

/* Variables and functions */
 int CHIP_RV770 ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*,...) ; 
 int /*<<< orphan*/  DRM_RADEON_VBLANK_CRTC1 ; 
 int EINVAL ; 
 int /*<<< orphan*/  RADEON_COLOR_FORMAT_ARGB8888 ; 
 int /*<<< orphan*/  RADEON_COLOR_FORMAT_RGB565 ; 
 scalar_t__ RADEON_CSQ_PRIBM_INDBM ; 
 scalar_t__ RADEON_CSQ_PRIBM_INDDIS ; 
 int RADEON_FAMILY_MASK ; 
 int RADEON_IS_AGP ; 
 int RADEON_IS_PCI ; 
 int RADEON_IS_PCIE ; 
 int RADEON_MAX_USEC_TIMEOUT ; 
 int RADEON_NEW_MEMMAP ; 
 int /*<<< orphan*/  RADEON_RING_HIGH_MARK ; 
 void* drm_core_findmap (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_core_ioremap_wc (TYPE_15__*,struct drm_device*) ; 
 int /*<<< orphan*/  drm_getsarea (struct drm_device*) ; 
 void* drm_order (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int r600_cp_init_microcode (TYPE_6__*) ; 
 int /*<<< orphan*/  r600_cp_init_ring_buffer (struct drm_device*,TYPE_6__*,struct drm_file*) ; 
 int /*<<< orphan*/  r600_cp_load_microcode (TYPE_6__*) ; 
 int /*<<< orphan*/  r600_cs_legacy_init () ; 
 int /*<<< orphan*/  r600_do_cleanup_cp (struct drm_device*) ; 
 int /*<<< orphan*/  r600_do_engine_reset (struct drm_device*) ; 
 int /*<<< orphan*/  r600_page_table_init (struct drm_device*) ; 
 int /*<<< orphan*/  r600_test_writeback (TYPE_6__*) ; 
 int /*<<< orphan*/  r600_vm_init (struct drm_device*) ; 
 int /*<<< orphan*/  r700_cp_load_microcode (TYPE_6__*) ; 
 int /*<<< orphan*/  r700_vm_init (struct drm_device*) ; 
 int radeon_no_wb ; 
 int radeon_read_fb_location (TYPE_6__*) ; 

int r600_do_init_cp(struct drm_device *dev, drm_radeon_init_t *init,
		    struct drm_file *file_priv)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	struct drm_radeon_master_private *master_priv = file_priv->master->driver_priv;

	DRM_DEBUG("\n");

	mutex_init(&dev_priv->cs_mutex);
	r600_cs_legacy_init();
	/* if we require new memory map but we don't have it fail */
	if ((dev_priv->flags & RADEON_NEW_MEMMAP) && !dev_priv->new_memmap) {
		DRM_ERROR("Cannot initialise DRM on this card\nThis card requires a new X.org DDX for 3D\n");
		r600_do_cleanup_cp(dev);
		return -EINVAL;
	}

	if (init->is_pci && (dev_priv->flags & RADEON_IS_AGP)) {
		DRM_DEBUG("Forcing AGP card to PCI mode\n");
		dev_priv->flags &= ~RADEON_IS_AGP;
		/* The writeback test succeeds, but when writeback is enabled,
		 * the ring buffer read ptr update fails after first 128 bytes.
		 */
		radeon_no_wb = 1;
	} else if (!(dev_priv->flags & (RADEON_IS_AGP | RADEON_IS_PCI | RADEON_IS_PCIE))
		 && !init->is_pci) {
		DRM_DEBUG("Restoring AGP flag\n");
		dev_priv->flags |= RADEON_IS_AGP;
	}

	dev_priv->usec_timeout = init->usec_timeout;
	if (dev_priv->usec_timeout < 1 ||
	    dev_priv->usec_timeout > RADEON_MAX_USEC_TIMEOUT) {
		DRM_DEBUG("TIMEOUT problem!\n");
		r600_do_cleanup_cp(dev);
		return -EINVAL;
	}

	/* Enable vblank on CRTC1 for older X servers
	 */
	dev_priv->vblank_crtc = DRM_RADEON_VBLANK_CRTC1;
	dev_priv->do_boxes = 0;
	dev_priv->cp_mode = init->cp_mode;

	/* We don't support anything other than bus-mastering ring mode,
	 * but the ring can be in either AGP or PCI space for the ring
	 * read pointer.
	 */
	if ((init->cp_mode != RADEON_CSQ_PRIBM_INDDIS) &&
	    (init->cp_mode != RADEON_CSQ_PRIBM_INDBM)) {
		DRM_DEBUG("BAD cp_mode (%x)!\n", init->cp_mode);
		r600_do_cleanup_cp(dev);
		return -EINVAL;
	}

	switch (init->fb_bpp) {
	case 16:
		dev_priv->color_fmt = RADEON_COLOR_FORMAT_RGB565;
		break;
	case 32:
	default:
		dev_priv->color_fmt = RADEON_COLOR_FORMAT_ARGB8888;
		break;
	}
	dev_priv->front_offset = init->front_offset;
	dev_priv->front_pitch = init->front_pitch;
	dev_priv->back_offset = init->back_offset;
	dev_priv->back_pitch = init->back_pitch;

	dev_priv->ring_offset = init->ring_offset;
	dev_priv->ring_rptr_offset = init->ring_rptr_offset;
	dev_priv->buffers_offset = init->buffers_offset;
	dev_priv->gart_textures_offset = init->gart_textures_offset;

	master_priv->sarea = drm_getsarea(dev);
	if (!master_priv->sarea) {
		DRM_ERROR("could not find sarea!\n");
		r600_do_cleanup_cp(dev);
		return -EINVAL;
	}

	dev_priv->cp_ring = drm_core_findmap(dev, init->ring_offset);
	if (!dev_priv->cp_ring) {
		DRM_ERROR("could not find cp ring region!\n");
		r600_do_cleanup_cp(dev);
		return -EINVAL;
	}
	dev_priv->ring_rptr = drm_core_findmap(dev, init->ring_rptr_offset);
	if (!dev_priv->ring_rptr) {
		DRM_ERROR("could not find ring read pointer!\n");
		r600_do_cleanup_cp(dev);
		return -EINVAL;
	}
	dev->agp_buffer_token = init->buffers_offset;
	dev->agp_buffer_map = drm_core_findmap(dev, init->buffers_offset);
	if (!dev->agp_buffer_map) {
		DRM_ERROR("could not find dma buffer region!\n");
		r600_do_cleanup_cp(dev);
		return -EINVAL;
	}

	if (init->gart_textures_offset) {
		dev_priv->gart_textures =
		    drm_core_findmap(dev, init->gart_textures_offset);
		if (!dev_priv->gart_textures) {
			DRM_ERROR("could not find GART texture region!\n");
			r600_do_cleanup_cp(dev);
			return -EINVAL;
		}
	}

#if __OS_HAS_AGP
	/* XXX */
	if (dev_priv->flags & RADEON_IS_AGP) {
		drm_core_ioremap_wc(dev_priv->cp_ring, dev);
		drm_core_ioremap_wc(dev_priv->ring_rptr, dev);
		drm_core_ioremap_wc(dev->agp_buffer_map, dev);
		if (!dev_priv->cp_ring->handle ||
		    !dev_priv->ring_rptr->handle ||
		    !dev->agp_buffer_map->handle) {
			DRM_ERROR("could not find ioremap agp regions!\n");
			r600_do_cleanup_cp(dev);
			return -EINVAL;
		}
	} else
#endif
	{
		dev_priv->cp_ring->handle = (void *)(unsigned long)dev_priv->cp_ring->offset;
		dev_priv->ring_rptr->handle =
			(void *)(unsigned long)dev_priv->ring_rptr->offset;
		dev->agp_buffer_map->handle =
			(void *)(unsigned long)dev->agp_buffer_map->offset;

		DRM_DEBUG("dev_priv->cp_ring->handle %p\n",
			  dev_priv->cp_ring->handle);
		DRM_DEBUG("dev_priv->ring_rptr->handle %p\n",
			  dev_priv->ring_rptr->handle);
		DRM_DEBUG("dev->agp_buffer_map->handle %p\n",
			  dev->agp_buffer_map->handle);
	}

	dev_priv->fb_location = (radeon_read_fb_location(dev_priv) & 0xffff) << 24;
	dev_priv->fb_size =
		(((radeon_read_fb_location(dev_priv) & 0xffff0000u) << 8) + 0x1000000)
		- dev_priv->fb_location;

	dev_priv->front_pitch_offset = (((dev_priv->front_pitch / 64) << 22) |
					((dev_priv->front_offset
					  + dev_priv->fb_location) >> 10));

	dev_priv->back_pitch_offset = (((dev_priv->back_pitch / 64) << 22) |
				       ((dev_priv->back_offset
					 + dev_priv->fb_location) >> 10));

	dev_priv->depth_pitch_offset = (((dev_priv->depth_pitch / 64) << 22) |
					((dev_priv->depth_offset
					  + dev_priv->fb_location) >> 10));

	dev_priv->gart_size = init->gart_size;

	/* New let's set the memory map ... */
	if (dev_priv->new_memmap) {
		u32 base = 0;

		DRM_INFO("Setting GART location based on new memory map\n");

		/* If using AGP, try to locate the AGP aperture at the same
		 * location in the card and on the bus, though we have to
		 * align it down.
		 */
#if __OS_HAS_AGP
		/* XXX */
		if (dev_priv->flags & RADEON_IS_AGP) {
			base = dev->agp->base;
			/* Check if valid */
			if ((base + dev_priv->gart_size - 1) >= dev_priv->fb_location &&
			    base < (dev_priv->fb_location + dev_priv->fb_size - 1)) {
				DRM_INFO("Can't use AGP base @0x%08lx, won't fit\n",
					 dev->agp->base);
				base = 0;
			}
		}
#endif
		/* If not or if AGP is at 0 (Macs), try to put it elsewhere */
		if (base == 0) {
			base = dev_priv->fb_location + dev_priv->fb_size;
			if (base < dev_priv->fb_location ||
			    ((base + dev_priv->gart_size) & 0xfffffffful) < base)
				base = dev_priv->fb_location
					- dev_priv->gart_size;
		}
		dev_priv->gart_vm_start = base & 0xffc00000u;
		if (dev_priv->gart_vm_start != base)
			DRM_INFO("GART aligned down from 0x%08x to 0x%08x\n",
				 base, dev_priv->gart_vm_start);
	}

#if __OS_HAS_AGP
	/* XXX */
	if (dev_priv->flags & RADEON_IS_AGP)
		dev_priv->gart_buffers_offset = (dev->agp_buffer_map->offset
						 - dev->agp->base
						 + dev_priv->gart_vm_start);
	else
#endif
		dev_priv->gart_buffers_offset = (dev->agp_buffer_map->offset
						 - (unsigned long)dev->sg->virtual
						 + dev_priv->gart_vm_start);

	DRM_DEBUG("fb 0x%08x size %d\n",
		  (unsigned int) dev_priv->fb_location,
		  (unsigned int) dev_priv->fb_size);
	DRM_DEBUG("dev_priv->gart_size %d\n", dev_priv->gart_size);
	DRM_DEBUG("dev_priv->gart_vm_start 0x%08x\n",
		  (unsigned int) dev_priv->gart_vm_start);
	DRM_DEBUG("dev_priv->gart_buffers_offset 0x%08lx\n",
		  dev_priv->gart_buffers_offset);

	dev_priv->ring.start = (u32 *) dev_priv->cp_ring->handle;
	dev_priv->ring.end = ((u32 *) dev_priv->cp_ring->handle
			      + init->ring_size / sizeof(u32));
	dev_priv->ring.size = init->ring_size;
	dev_priv->ring.size_l2qw = drm_order(init->ring_size / 8);

	dev_priv->ring.rptr_update = /* init->rptr_update */ 4096;
	dev_priv->ring.rptr_update_l2qw = drm_order(/* init->rptr_update */ 4096 / 8);

	dev_priv->ring.fetch_size = /* init->fetch_size */ 32;
	dev_priv->ring.fetch_size_l2ow = drm_order(/* init->fetch_size */ 32 / 16);

	dev_priv->ring.tail_mask = (dev_priv->ring.size / sizeof(u32)) - 1;

	dev_priv->ring.high_mark = RADEON_RING_HIGH_MARK;

#if __OS_HAS_AGP
	if (dev_priv->flags & RADEON_IS_AGP) {
		/* XXX turn off pcie gart */
	} else
#endif
	{
		dev_priv->gart_info.table_mask = DMA_BIT_MASK(32);
		/* if we have an offset set from userspace */
		if (!dev_priv->pcigart_offset_set) {
			DRM_ERROR("Need gart offset from userspace\n");
			r600_do_cleanup_cp(dev);
			return -EINVAL;
		}

		DRM_DEBUG("Using gart offset 0x%08lx\n", dev_priv->pcigart_offset);

		dev_priv->gart_info.bus_addr =
			dev_priv->pcigart_offset + dev_priv->fb_location;
		dev_priv->gart_info.mapping.offset =
			dev_priv->pcigart_offset + dev_priv->fb_aper_offset;
		dev_priv->gart_info.mapping.size =
			dev_priv->gart_info.table_size;

		drm_core_ioremap_wc(&dev_priv->gart_info.mapping, dev);
		if (!dev_priv->gart_info.mapping.handle) {
			DRM_ERROR("ioremap failed.\n");
			r600_do_cleanup_cp(dev);
			return -EINVAL;
		}

		dev_priv->gart_info.addr =
			dev_priv->gart_info.mapping.handle;

		DRM_DEBUG("Setting phys_pci_gart to %p %08lX\n",
			  dev_priv->gart_info.addr,
			  dev_priv->pcigart_offset);

		if (!r600_page_table_init(dev)) {
			DRM_ERROR("Failed to init GART table\n");
			r600_do_cleanup_cp(dev);
			return -EINVAL;
		}

		if (((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_RV770))
			r700_vm_init(dev);
		else
			r600_vm_init(dev);
	}

	if (!dev_priv->me_fw || !dev_priv->pfp_fw) {
		int err = r600_cp_init_microcode(dev_priv);
		if (err) {
			DRM_ERROR("Failed to load firmware!\n");
			r600_do_cleanup_cp(dev);
			return err;
		}
	}
	if (((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_RV770))
		r700_cp_load_microcode(dev_priv);
	else
		r600_cp_load_microcode(dev_priv);

	r600_cp_init_ring_buffer(dev, dev_priv, file_priv);

	dev_priv->last_buf = 0;

	r600_do_engine_reset(dev);
	r600_test_writeback(dev_priv);

	return 0;
}