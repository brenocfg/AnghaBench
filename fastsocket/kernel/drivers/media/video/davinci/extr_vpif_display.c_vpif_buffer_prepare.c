#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vpif_fh {TYPE_1__* channel; } ;
struct videobuf_queue {scalar_t__ type; scalar_t__ streaming; struct vpif_fh* priv_data; } ;
struct videobuf_buffer {scalar_t__ state; int width; int height; int size; int field; unsigned long boff; int /*<<< orphan*/  baddr; } ;
struct common_obj {int width; int height; scalar_t__ memory; unsigned long ytop_off; unsigned long ybtm_off; unsigned long ctop_off; unsigned long cbtm_off; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;
struct TYPE_2__ {struct common_obj* common; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ISALIGNED (unsigned long) ; 
 scalar_t__ V4L2_BUF_TYPE_SLICED_VBI_OUTPUT ; 
 scalar_t__ V4L2_MEMORY_USERPTR ; 
 scalar_t__ VIDEOBUF_NEEDS_INIT ; 
 scalar_t__ VIDEOBUF_PREPARED ; 
 size_t VPIF_VIDEO_INDEX ; 
 int /*<<< orphan*/  vpif_err (char*) ; 
 unsigned long vpif_uservirt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpif_buffer_prepare(struct videobuf_queue *q,
			       struct videobuf_buffer *vb,
			       enum v4l2_field field)
{
	struct vpif_fh *fh = q->priv_data;
	struct common_obj *common;
	unsigned long addr;

	common = &fh->channel->common[VPIF_VIDEO_INDEX];
	if (VIDEOBUF_NEEDS_INIT == vb->state) {
		vb->width	= common->width;
		vb->height	= common->height;
		vb->size	= vb->width * vb->height;
		vb->field	= field;
	}
	vb->state = VIDEOBUF_PREPARED;

	/* if user pointer memory mechanism is used, get the physical
	 * address of the buffer */
	if (V4L2_MEMORY_USERPTR == common->memory) {
		if (!vb->baddr) {
			vpif_err("buffer_address is 0\n");
			return -EINVAL;
		}

		vb->boff = vpif_uservirt_to_phys(vb->baddr);
		if (!ISALIGNED(vb->boff))
			goto buf_align_exit;
	}

	addr = vb->boff;
	if (q->streaming && (V4L2_BUF_TYPE_SLICED_VBI_OUTPUT != q->type)) {
		if (!ISALIGNED(addr + common->ytop_off) ||
		    !ISALIGNED(addr + common->ybtm_off) ||
		    !ISALIGNED(addr + common->ctop_off) ||
		    !ISALIGNED(addr + common->cbtm_off))
			goto buf_align_exit;
	}
	return 0;

buf_align_exit:
	vpif_err("buffer offset not aligned to 8 bytes\n");
	return -EINVAL;
}