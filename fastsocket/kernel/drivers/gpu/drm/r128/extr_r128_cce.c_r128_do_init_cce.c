#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct drm_device {void* dev_private; TYPE_3__* sg; TYPE_1__* agp; TYPE_12__* agp_buffer_map; int /*<<< orphan*/  agp_buffer_token; } ;
struct TYPE_20__ {scalar_t__ last_dispatch; scalar_t__ last_frame; } ;
typedef  TYPE_4__ drm_r128_sarea_t ;
struct TYPE_16__ {scalar_t__ bus_addr; int /*<<< orphan*/  gart_reg_if; int /*<<< orphan*/ * addr; int /*<<< orphan*/  table_size; int /*<<< orphan*/  gart_table_location; int /*<<< orphan*/  table_mask; } ;
struct TYPE_18__ {int size; int tail_mask; int high_mark; int /*<<< orphan*/  size_l2qw; int /*<<< orphan*/ * end; int /*<<< orphan*/ * start; } ;
struct TYPE_21__ {int usec_timeout; int cce_mode; int cce_fifo_size; int front_offset; int front_pitch; int back_offset; int back_pitch; int depth_offset; int depth_pitch; int span_offset; int front_pitch_offset_c; int back_pitch_offset_c; int depth_pitch_offset_c; int span_pitch_offset_c; unsigned long cce_buffers_offset; TYPE_13__ gart_info; scalar_t__ is_pci; TYPE_4__* sarea_priv; TYPE_2__ ring; TYPE_12__* cce_ring; TYPE_12__* ring_rptr; TYPE_11__* sarea; void* agp_textures; void* mmio; void* depth_fmt; void* color_fmt; int /*<<< orphan*/  idle_count; } ;
typedef  TYPE_5__ drm_r128_private_t ;
struct TYPE_22__ {int usec_timeout; int cce_mode; int fb_bpp; int front_offset; int front_pitch; int back_offset; int back_pitch; int depth_bpp; int depth_offset; int depth_pitch; int span_offset; int sarea_priv_offset; int ring_size; int /*<<< orphan*/  agp_textures_offset; int /*<<< orphan*/  buffers_offset; int /*<<< orphan*/  ring_rptr_offset; int /*<<< orphan*/  ring_offset; int /*<<< orphan*/  mmio_offset; scalar_t__ is_pci; } ;
typedef  TYPE_6__ drm_r128_init_t ;
struct TYPE_19__ {scalar_t__ virtual; } ;
struct TYPE_17__ {unsigned long base; } ;
struct TYPE_15__ {void* handle; scalar_t__ offset; } ;
struct TYPE_14__ {scalar_t__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRM_ATI_GART_MAIN ; 
 int /*<<< orphan*/  DRM_ATI_GART_PCI ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* R128_DATATYPE_ARGB8888 ; 
 void* R128_DATATYPE_RGB565 ; 
 int R128_DST_TILE ; 
 int /*<<< orphan*/  R128_LAST_DISPATCH_REG ; 
 int /*<<< orphan*/  R128_LAST_FRAME_REG ; 
 int R128_MAX_USEC_TIMEOUT ; 
 int /*<<< orphan*/  R128_PCIGART_TABLE_SIZE ; 
 int /*<<< orphan*/  R128_PCI_GART_PAGE ; 
#define  R128_PM4_128BM_64INDBM 137 
#define  R128_PM4_128PIO_64INDBM 136 
#define  R128_PM4_192BM 135 
#define  R128_PM4_192PIO 134 
#define  R128_PM4_64BM_128INDBM 133 
#define  R128_PM4_64BM_64VCBM_64INDBM 132 
#define  R128_PM4_64PIO_128INDBM 131 
#define  R128_PM4_64PIO_64VCBM_64INDBM 130 
#define  R128_PM4_64PIO_64VCPIO_64INDPIO 129 
#define  R128_PM4_NONPM4 128 
 int /*<<< orphan*/  R128_WRITE (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_ati_pcigart_init (struct drm_device*,TYPE_13__*) ; 
 void* drm_core_findmap (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_core_ioremap_wc (TYPE_12__*,struct drm_device*) ; 
 TYPE_11__* drm_getsarea (struct drm_device*) ; 
 int /*<<< orphan*/  drm_order (int) ; 
 TYPE_5__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r128_cce_init_ring_buffer (struct drm_device*,TYPE_5__*) ; 
 int r128_cce_load_microcode (TYPE_5__*) ; 
 int /*<<< orphan*/  r128_do_cleanup_cce (struct drm_device*) ; 
 int /*<<< orphan*/  r128_do_engine_reset (struct drm_device*) ; 

__attribute__((used)) static int r128_do_init_cce(struct drm_device *dev, drm_r128_init_t *init)
{
	drm_r128_private_t *dev_priv;
	int rc;

	DRM_DEBUG("\n");

	if (dev->dev_private) {
		DRM_DEBUG("called when already initialized\n");
		return -EINVAL;
	}

	dev_priv = kzalloc(sizeof(drm_r128_private_t), GFP_KERNEL);
	if (dev_priv == NULL)
		return -ENOMEM;

	dev_priv->is_pci = init->is_pci;

	if (dev_priv->is_pci && !dev->sg) {
		DRM_ERROR("PCI GART memory not allocated!\n");
		dev->dev_private = (void *)dev_priv;
		r128_do_cleanup_cce(dev);
		return -EINVAL;
	}

	dev_priv->usec_timeout = init->usec_timeout;
	if (dev_priv->usec_timeout < 1 ||
	    dev_priv->usec_timeout > R128_MAX_USEC_TIMEOUT) {
		DRM_DEBUG("TIMEOUT problem!\n");
		dev->dev_private = (void *)dev_priv;
		r128_do_cleanup_cce(dev);
		return -EINVAL;
	}

	dev_priv->cce_mode = init->cce_mode;

	/* GH: Simple idle check.
	 */
	atomic_set(&dev_priv->idle_count, 0);

	/* We don't support anything other than bus-mastering ring mode,
	 * but the ring can be in either AGP or PCI space for the ring
	 * read pointer.
	 */
	if ((init->cce_mode != R128_PM4_192BM) &&
	    (init->cce_mode != R128_PM4_128BM_64INDBM) &&
	    (init->cce_mode != R128_PM4_64BM_128INDBM) &&
	    (init->cce_mode != R128_PM4_64BM_64VCBM_64INDBM)) {
		DRM_DEBUG("Bad cce_mode!\n");
		dev->dev_private = (void *)dev_priv;
		r128_do_cleanup_cce(dev);
		return -EINVAL;
	}

	switch (init->cce_mode) {
	case R128_PM4_NONPM4:
		dev_priv->cce_fifo_size = 0;
		break;
	case R128_PM4_192PIO:
	case R128_PM4_192BM:
		dev_priv->cce_fifo_size = 192;
		break;
	case R128_PM4_128PIO_64INDBM:
	case R128_PM4_128BM_64INDBM:
		dev_priv->cce_fifo_size = 128;
		break;
	case R128_PM4_64PIO_128INDBM:
	case R128_PM4_64BM_128INDBM:
	case R128_PM4_64PIO_64VCBM_64INDBM:
	case R128_PM4_64BM_64VCBM_64INDBM:
	case R128_PM4_64PIO_64VCPIO_64INDPIO:
		dev_priv->cce_fifo_size = 64;
		break;
	}

	switch (init->fb_bpp) {
	case 16:
		dev_priv->color_fmt = R128_DATATYPE_RGB565;
		break;
	case 32:
	default:
		dev_priv->color_fmt = R128_DATATYPE_ARGB8888;
		break;
	}
	dev_priv->front_offset = init->front_offset;
	dev_priv->front_pitch = init->front_pitch;
	dev_priv->back_offset = init->back_offset;
	dev_priv->back_pitch = init->back_pitch;

	switch (init->depth_bpp) {
	case 16:
		dev_priv->depth_fmt = R128_DATATYPE_RGB565;
		break;
	case 24:
	case 32:
	default:
		dev_priv->depth_fmt = R128_DATATYPE_ARGB8888;
		break;
	}
	dev_priv->depth_offset = init->depth_offset;
	dev_priv->depth_pitch = init->depth_pitch;
	dev_priv->span_offset = init->span_offset;

	dev_priv->front_pitch_offset_c = (((dev_priv->front_pitch / 8) << 21) |
					  (dev_priv->front_offset >> 5));
	dev_priv->back_pitch_offset_c = (((dev_priv->back_pitch / 8) << 21) |
					 (dev_priv->back_offset >> 5));
	dev_priv->depth_pitch_offset_c = (((dev_priv->depth_pitch / 8) << 21) |
					  (dev_priv->depth_offset >> 5) |
					  R128_DST_TILE);
	dev_priv->span_pitch_offset_c = (((dev_priv->depth_pitch / 8) << 21) |
					 (dev_priv->span_offset >> 5));

	dev_priv->sarea = drm_getsarea(dev);
	if (!dev_priv->sarea) {
		DRM_ERROR("could not find sarea!\n");
		dev->dev_private = (void *)dev_priv;
		r128_do_cleanup_cce(dev);
		return -EINVAL;
	}

	dev_priv->mmio = drm_core_findmap(dev, init->mmio_offset);
	if (!dev_priv->mmio) {
		DRM_ERROR("could not find mmio region!\n");
		dev->dev_private = (void *)dev_priv;
		r128_do_cleanup_cce(dev);
		return -EINVAL;
	}
	dev_priv->cce_ring = drm_core_findmap(dev, init->ring_offset);
	if (!dev_priv->cce_ring) {
		DRM_ERROR("could not find cce ring region!\n");
		dev->dev_private = (void *)dev_priv;
		r128_do_cleanup_cce(dev);
		return -EINVAL;
	}
	dev_priv->ring_rptr = drm_core_findmap(dev, init->ring_rptr_offset);
	if (!dev_priv->ring_rptr) {
		DRM_ERROR("could not find ring read pointer!\n");
		dev->dev_private = (void *)dev_priv;
		r128_do_cleanup_cce(dev);
		return -EINVAL;
	}
	dev->agp_buffer_token = init->buffers_offset;
	dev->agp_buffer_map = drm_core_findmap(dev, init->buffers_offset);
	if (!dev->agp_buffer_map) {
		DRM_ERROR("could not find dma buffer region!\n");
		dev->dev_private = (void *)dev_priv;
		r128_do_cleanup_cce(dev);
		return -EINVAL;
	}

	if (!dev_priv->is_pci) {
		dev_priv->agp_textures =
		    drm_core_findmap(dev, init->agp_textures_offset);
		if (!dev_priv->agp_textures) {
			DRM_ERROR("could not find agp texture region!\n");
			dev->dev_private = (void *)dev_priv;
			r128_do_cleanup_cce(dev);
			return -EINVAL;
		}
	}

	dev_priv->sarea_priv =
	    (drm_r128_sarea_t *) ((u8 *) dev_priv->sarea->handle +
				  init->sarea_priv_offset);

#if __OS_HAS_AGP
	if (!dev_priv->is_pci) {
		drm_core_ioremap_wc(dev_priv->cce_ring, dev);
		drm_core_ioremap_wc(dev_priv->ring_rptr, dev);
		drm_core_ioremap_wc(dev->agp_buffer_map, dev);
		if (!dev_priv->cce_ring->handle ||
		    !dev_priv->ring_rptr->handle ||
		    !dev->agp_buffer_map->handle) {
			DRM_ERROR("Could not ioremap agp regions!\n");
			dev->dev_private = (void *)dev_priv;
			r128_do_cleanup_cce(dev);
			return -ENOMEM;
		}
	} else
#endif
	{
		dev_priv->cce_ring->handle =
			(void *)(unsigned long)dev_priv->cce_ring->offset;
		dev_priv->ring_rptr->handle =
			(void *)(unsigned long)dev_priv->ring_rptr->offset;
		dev->agp_buffer_map->handle =
			(void *)(unsigned long)dev->agp_buffer_map->offset;
	}

#if __OS_HAS_AGP
	if (!dev_priv->is_pci)
		dev_priv->cce_buffers_offset = dev->agp->base;
	else
#endif
		dev_priv->cce_buffers_offset = (unsigned long)dev->sg->virtual;

	dev_priv->ring.start = (u32 *) dev_priv->cce_ring->handle;
	dev_priv->ring.end = ((u32 *) dev_priv->cce_ring->handle
			      + init->ring_size / sizeof(u32));
	dev_priv->ring.size = init->ring_size;
	dev_priv->ring.size_l2qw = drm_order(init->ring_size / 8);

	dev_priv->ring.tail_mask = (dev_priv->ring.size / sizeof(u32)) - 1;

	dev_priv->ring.high_mark = 128;

	dev_priv->sarea_priv->last_frame = 0;
	R128_WRITE(R128_LAST_FRAME_REG, dev_priv->sarea_priv->last_frame);

	dev_priv->sarea_priv->last_dispatch = 0;
	R128_WRITE(R128_LAST_DISPATCH_REG, dev_priv->sarea_priv->last_dispatch);

#if __OS_HAS_AGP
	if (dev_priv->is_pci) {
#endif
		dev_priv->gart_info.table_mask = DMA_BIT_MASK(32);
		dev_priv->gart_info.gart_table_location = DRM_ATI_GART_MAIN;
		dev_priv->gart_info.table_size = R128_PCIGART_TABLE_SIZE;
		dev_priv->gart_info.addr = NULL;
		dev_priv->gart_info.bus_addr = 0;
		dev_priv->gart_info.gart_reg_if = DRM_ATI_GART_PCI;
		if (!drm_ati_pcigart_init(dev, &dev_priv->gart_info)) {
			DRM_ERROR("failed to init PCI GART!\n");
			dev->dev_private = (void *)dev_priv;
			r128_do_cleanup_cce(dev);
			return -ENOMEM;
		}
		R128_WRITE(R128_PCI_GART_PAGE, dev_priv->gart_info.bus_addr);
#if __OS_HAS_AGP
	}
#endif

	r128_cce_init_ring_buffer(dev, dev_priv);
	rc = r128_cce_load_microcode(dev_priv);

	dev->dev_private = (void *)dev_priv;

	r128_do_engine_reset(dev);

	if (rc) {
		DRM_ERROR("Failed to load firmware!\n");
		r128_do_cleanup_cce(dev);
	}

	return rc;
}