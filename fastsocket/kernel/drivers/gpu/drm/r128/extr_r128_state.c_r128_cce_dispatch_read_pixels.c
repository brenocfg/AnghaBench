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
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_4__ {int depth_pitch; int depth_fmt; int depth_pitch_offset_c; int span_pitch_offset_c; } ;
typedef  TYPE_1__ drm_r128_private_t ;
struct TYPE_5__ {int n; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ drm_r128_depth_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int CCE_PACKET3 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ DRM_COPY_FROM_USER (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int EFAULT ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int /*<<< orphan*/  R128_CNTL_BITBLT_MULTI ; 
 int R128_DP_SRC_SOURCE_MEMORY ; 
 int R128_GMC_BRUSH_NONE ; 
 int R128_GMC_CLR_CMP_CNTL_DIS ; 
 int R128_GMC_DST_PITCH_OFFSET_CNTL ; 
 int R128_GMC_SRC_DATATYPE_COLOR ; 
 int R128_GMC_SRC_PITCH_OFFSET_CNTL ; 
 int R128_GMC_WR_MSK_DIS ; 
 int R128_ROP3_S ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r128_cce_dispatch_read_pixels(struct drm_device *dev,
					 drm_r128_depth_t *depth)
{
	drm_r128_private_t *dev_priv = dev->dev_private;
	int count, *x, *y;
	int i, xbuf_size, ybuf_size;
	RING_LOCALS;
	DRM_DEBUG("\n");

	count = depth->n;
	if (count > 4096 || count <= 0)
		return -EMSGSIZE;

	if (count > dev_priv->depth_pitch)
		count = dev_priv->depth_pitch;

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
	if (DRM_COPY_FROM_USER(y, depth->y, ybuf_size)) {
		kfree(x);
		kfree(y);
		return -EFAULT;
	}

	for (i = 0; i < count; i++) {
		BEGIN_RING(7);

		OUT_RING(CCE_PACKET3(R128_CNTL_BITBLT_MULTI, 5));
		OUT_RING(R128_GMC_SRC_PITCH_OFFSET_CNTL |
			 R128_GMC_DST_PITCH_OFFSET_CNTL |
			 R128_GMC_BRUSH_NONE |
			 (dev_priv->depth_fmt << 8) |
			 R128_GMC_SRC_DATATYPE_COLOR |
			 R128_ROP3_S |
			 R128_DP_SRC_SOURCE_MEMORY |
			 R128_GMC_CLR_CMP_CNTL_DIS | R128_GMC_WR_MSK_DIS);

		OUT_RING(dev_priv->depth_pitch_offset_c);
		OUT_RING(dev_priv->span_pitch_offset_c);

		OUT_RING((x[i] << 16) | y[i]);
		OUT_RING((i << 16) | 0);
		OUT_RING((1 << 16) | 1);

		ADVANCE_RING();
	}

	kfree(x);
	kfree(y);

	return 0;
}