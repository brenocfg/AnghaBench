#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vpfe_fh {struct vpfe_device* vpfe_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_5__ {TYPE_1__ pix; } ;
struct TYPE_6__ {TYPE_2__ fmt; } ;
struct vpfe_device {TYPE_3__ fmt; int /*<<< orphan*/  v4l2_dev; } ;
struct videobuf_queue {struct vpfe_fh* priv_data; } ;
struct videobuf_buffer {scalar_t__ state; int field; int /*<<< orphan*/  size; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;

/* Variables and functions */
 scalar_t__ VIDEOBUF_NEEDS_INIT ; 
 scalar_t__ VIDEOBUF_PREPARED ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int vpfe_videobuf_prepare(struct videobuf_queue *vq,
				struct videobuf_buffer *vb,
				enum v4l2_field field)
{
	struct vpfe_fh *fh = vq->priv_data;
	struct vpfe_device *vpfe_dev = fh->vpfe_dev;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_buffer_prepare\n");

	/* If buffer is not initialized, initialize it */
	if (VIDEOBUF_NEEDS_INIT == vb->state) {
		vb->width = vpfe_dev->fmt.fmt.pix.width;
		vb->height = vpfe_dev->fmt.fmt.pix.height;
		vb->size = vpfe_dev->fmt.fmt.pix.sizeimage;
		vb->field = field;
	}
	vb->state = VIDEOBUF_PREPARED;
	return 0;
}