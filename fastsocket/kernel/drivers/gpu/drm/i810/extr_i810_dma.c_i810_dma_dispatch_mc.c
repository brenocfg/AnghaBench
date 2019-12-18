#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct drm_device {TYPE_1__* agp; TYPE_3__* dev_private; } ;
struct drm_buf {scalar_t__ bus_address; TYPE_4__* dev_private; } ;
struct TYPE_6__ {int dirty; } ;
typedef  TYPE_2__ drm_i810_sarea_t ;
struct TYPE_7__ {unsigned long counter; TYPE_2__* sarea_priv; } ;
typedef  TYPE_3__ drm_i810_private_t ;
struct TYPE_8__ {scalar_t__ currently_mapped; unsigned int my_use_idx; scalar_t__ virtual; int /*<<< orphan*/  in_use; } ;
typedef  TYPE_4__ drm_i810_buf_priv_t ;
struct TYPE_5__ {unsigned long base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_LP_RING () ; 
 unsigned long BB1_PROTECTED ; 
 int /*<<< orphan*/  BEGIN_LP_RING (int) ; 
 unsigned int CMD_OP_BATCH_BUFFER ; 
 unsigned int CMD_STORE_DWORD_IDX ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int I810_BUF_CLIENT ; 
 unsigned int I810_BUF_FREE ; 
 int /*<<< orphan*/  I810_BUF_HARDWARE ; 
 scalar_t__ I810_BUF_MAPPED ; 
 int /*<<< orphan*/  OUT_RING (unsigned int) ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int cmpxchg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i810_kernel_lost_context (struct drm_device*) ; 
 int /*<<< orphan*/  i810_unmap_buffer (struct drm_buf*) ; 

__attribute__((used)) static void i810_dma_dispatch_mc(struct drm_device *dev, struct drm_buf *buf, int used,
				 unsigned int last_render)
{
	drm_i810_private_t *dev_priv = dev->dev_private;
	drm_i810_buf_priv_t *buf_priv = buf->dev_private;
	drm_i810_sarea_t *sarea_priv = dev_priv->sarea_priv;
	unsigned long address = (unsigned long)buf->bus_address;
	unsigned long start = address - dev->agp->base;
	int u;
	RING_LOCALS;

	i810_kernel_lost_context(dev);

	u = cmpxchg(buf_priv->in_use, I810_BUF_CLIENT, I810_BUF_HARDWARE);
	if (u != I810_BUF_CLIENT)
		DRM_DEBUG("MC found buffer that isn't mine!\n");

	if (used > 4 * 1024)
		used = 0;

	sarea_priv->dirty = 0x7f;

	DRM_DEBUG("addr 0x%lx, used 0x%x\n", address, used);

	dev_priv->counter++;
	DRM_DEBUG("dispatch counter : %ld\n", dev_priv->counter);
	DRM_DEBUG("start : %lx\n", start);
	DRM_DEBUG("used : %d\n", used);
	DRM_DEBUG("start + used - 4 : %ld\n", start + used - 4);

	if (buf_priv->currently_mapped == I810_BUF_MAPPED) {
		if (used & 4) {
			*(u32 *) ((char *) buf_priv->virtual + used) = 0;
			used += 4;
		}

		i810_unmap_buffer(buf);
	}
	BEGIN_LP_RING(4);
	OUT_RING(CMD_OP_BATCH_BUFFER);
	OUT_RING(start | BB1_PROTECTED);
	OUT_RING(start + used - 4);
	OUT_RING(0);
	ADVANCE_LP_RING();

	BEGIN_LP_RING(8);
	OUT_RING(CMD_STORE_DWORD_IDX);
	OUT_RING(buf_priv->my_use_idx);
	OUT_RING(I810_BUF_FREE);
	OUT_RING(0);

	OUT_RING(CMD_STORE_DWORD_IDX);
	OUT_RING(16);
	OUT_RING(last_render);
	OUT_RING(0);
	ADVANCE_LP_RING();
}