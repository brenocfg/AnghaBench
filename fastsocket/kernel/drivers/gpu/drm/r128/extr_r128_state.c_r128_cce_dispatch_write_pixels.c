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
typedef  int u8 ;
typedef  int u32 ;
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_4__ {int depth_fmt; int depth_pitch_offset_c; } ;
typedef  TYPE_1__ drm_r128_private_t ;
struct TYPE_5__ {int n; scalar_t__ mask; scalar_t__ buffer; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_2__ drm_r128_depth_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int CCE_PACKET3 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ DRM_COPY_FROM_USER (int*,scalar_t__,int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int EFAULT ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int /*<<< orphan*/  R128_CNTL_PAINT_MULTI ; 
 int R128_GMC_BRUSH_SOLID_COLOR ; 
 int R128_GMC_CLR_CMP_CNTL_DIS ; 
 int R128_GMC_DST_PITCH_OFFSET_CNTL ; 
 int R128_GMC_SRC_DATATYPE_COLOR ; 
 int R128_GMC_WR_MSK_DIS ; 
 int R128_ROP3_P ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r128_cce_dispatch_write_pixels(struct drm_device *dev,
					  drm_r128_depth_t *depth)
{
	drm_r128_private_t *dev_priv = dev->dev_private;
	int count, *x, *y;
	u32 *buffer;
	u8 *mask;
	int i, xbuf_size, ybuf_size, buffer_size, mask_size;
	RING_LOCALS;
	DRM_DEBUG("\n");

	count = depth->n;
	if (count > 4096 || count <= 0)
		return -EMSGSIZE;

	xbuf_size = count * sizeof(*x);
	ybuf_size = count * sizeof(*y);
	x = kmalloc(xbuf_size, GFP_KERNEL);
	if (x == NULL)
		return -ENOMEM;
	y = kmalloc(ybuf_size, GFP_KERNEL);
	if (y == NULL) {
		kfree(x);
		return -ENOMEM;
	}
	if (DRM_COPY_FROM_USER(x, depth->x, xbuf_size)) {
		kfree(x);
		kfree(y);
		return -EFAULT;
	}
	if (DRM_COPY_FROM_USER(y, depth->y, xbuf_size)) {
		kfree(x);
		kfree(y);
		return -EFAULT;
	}

	buffer_size = depth->n * sizeof(u32);
	buffer = kmalloc(buffer_size, GFP_KERNEL);
	if (buffer == NULL) {
		kfree(x);
		kfree(y);
		return -ENOMEM;
	}
	if (DRM_COPY_FROM_USER(buffer, depth->buffer, buffer_size)) {
		kfree(x);
		kfree(y);
		kfree(buffer);
		return -EFAULT;
	}

	if (depth->mask) {
		mask_size = depth->n * sizeof(u8);
		mask = kmalloc(mask_size, GFP_KERNEL);
		if (mask == NULL) {
			kfree(x);
			kfree(y);
			kfree(buffer);
			return -ENOMEM;
		}
		if (DRM_COPY_FROM_USER(mask, depth->mask, mask_size)) {
			kfree(x);
			kfree(y);
			kfree(buffer);
			kfree(mask);
			return -EFAULT;
		}

		for (i = 0; i < count; i++) {
			if (mask[i]) {
				BEGIN_RING(6);

				OUT_RING(CCE_PACKET3(R128_CNTL_PAINT_MULTI, 4));
				OUT_RING(R128_GMC_DST_PITCH_OFFSET_CNTL |
					 R128_GMC_BRUSH_SOLID_COLOR |
					 (dev_priv->depth_fmt << 8) |
					 R128_GMC_SRC_DATATYPE_COLOR |
					 R128_ROP3_P |
					 R128_GMC_CLR_CMP_CNTL_DIS |
					 R128_GMC_WR_MSK_DIS);

				OUT_RING(dev_priv->depth_pitch_offset_c);
				OUT_RING(buffer[i]);

				OUT_RING((x[i] << 16) | y[i]);
				OUT_RING((1 << 16) | 1);

				ADVANCE_RING();
			}
		}

		kfree(mask);
	} else {
		for (i = 0; i < count; i++) {
			BEGIN_RING(6);

			OUT_RING(CCE_PACKET3(R128_CNTL_PAINT_MULTI, 4));
			OUT_RING(R128_GMC_DST_PITCH_OFFSET_CNTL |
				 R128_GMC_BRUSH_SOLID_COLOR |
				 (dev_priv->depth_fmt << 8) |
				 R128_GMC_SRC_DATATYPE_COLOR |
				 R128_ROP3_P |
				 R128_GMC_CLR_CMP_CNTL_DIS |
				 R128_GMC_WR_MSK_DIS);

			OUT_RING(dev_priv->depth_pitch_offset_c);
			OUT_RING(buffer[i]);

			OUT_RING((x[i] << 16) | y[i]);
			OUT_RING((1 << 16) | 1);

			ADVANCE_RING();
		}
	}

	kfree(x);
	kfree(y);
	kfree(buffer);

	return 0;
}