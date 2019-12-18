#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct drm_clip_rect {int dummy; } ;
struct drm_buf {int dummy; } ;
struct TYPE_19__ {int /*<<< orphan*/  (* emit_clip_rect ) (TYPE_3__*,struct drm_clip_rect const*) ;} ;
typedef  TYPE_3__ drm_savage_private_t ;
struct TYPE_18__ {int cmd; } ;
struct TYPE_17__ {int /*<<< orphan*/  count; } ;
struct TYPE_20__ {TYPE_2__ cmd; TYPE_1__ idx; } ;
typedef  TYPE_4__ drm_savage_cmd_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 
#define  SAVAGE_CMD_DMA_IDX 131 
#define  SAVAGE_CMD_DMA_PRIM 130 
#define  SAVAGE_CMD_VB_IDX 129 
#define  SAVAGE_CMD_VB_PRIM 128 
 int savage_dispatch_dma_idx (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/  const*,struct drm_buf const*) ; 
 int savage_dispatch_dma_prim (TYPE_3__*,TYPE_4__*,struct drm_buf const*) ; 
 int savage_dispatch_vb_idx (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int,unsigned int) ; 
 int savage_dispatch_vb_prim (TYPE_3__*,TYPE_4__*,unsigned int const*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,struct drm_clip_rect const*) ; 

__attribute__((used)) static int savage_dispatch_draw(drm_savage_private_t * dev_priv,
				const drm_savage_cmd_header_t *start,
				const drm_savage_cmd_header_t *end,
				const struct drm_buf * dmabuf,
				const unsigned int *vtxbuf,
				unsigned int vb_size, unsigned int vb_stride,
				unsigned int nbox,
				const struct drm_clip_rect *boxes)
{
	unsigned int i, j;
	int ret;

	for (i = 0; i < nbox; ++i) {
		const drm_savage_cmd_header_t *cmdbuf;
		dev_priv->emit_clip_rect(dev_priv, &boxes[i]);

		cmdbuf = start;
		while (cmdbuf < end) {
			drm_savage_cmd_header_t cmd_header;
			cmd_header = *cmdbuf;
			cmdbuf++;
			switch (cmd_header.cmd.cmd) {
			case SAVAGE_CMD_DMA_PRIM:
				ret = savage_dispatch_dma_prim(
					dev_priv, &cmd_header, dmabuf);
				break;
			case SAVAGE_CMD_VB_PRIM:
				ret = savage_dispatch_vb_prim(
					dev_priv, &cmd_header,
					vtxbuf, vb_size, vb_stride);
				break;
			case SAVAGE_CMD_DMA_IDX:
				j = (cmd_header.idx.count + 3) / 4;
				/* j was check in savage_bci_cmdbuf */
				ret = savage_dispatch_dma_idx(dev_priv,
					&cmd_header, (const uint16_t *)cmdbuf,
					dmabuf);
				cmdbuf += j;
				break;
			case SAVAGE_CMD_VB_IDX:
				j = (cmd_header.idx.count + 3) / 4;
				/* j was check in savage_bci_cmdbuf */
				ret = savage_dispatch_vb_idx(dev_priv,
					&cmd_header, (const uint16_t *)cmdbuf,
					(const uint32_t *)vtxbuf, vb_size,
					vb_stride);
				cmdbuf += j;
				break;
			default:
				/* What's the best return code? EFAULT? */
				DRM_ERROR("IMPLEMENTATION ERROR: "
					  "non-drawing-command %d\n",
					  cmd_header.cmd.cmd);
				return -EINVAL;
			}

			if (ret != 0)
				return ret;
		}
	}

	return 0;
}