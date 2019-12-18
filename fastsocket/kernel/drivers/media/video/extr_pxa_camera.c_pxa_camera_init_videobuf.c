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
struct videobuf_queue {int dummy; } ;
struct soc_camera_host {struct pxa_camera_dev* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct soc_camera_device {int /*<<< orphan*/  video_lock; TYPE_1__ dev; } ;
struct pxa_camera_dev {int /*<<< orphan*/  lock; } ;
struct pxa_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  pxa_videobuf_ops ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  videobuf_queue_sg_init (struct videobuf_queue*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct soc_camera_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pxa_camera_init_videobuf(struct videobuf_queue *q,
			      struct soc_camera_device *icd)
{
	struct soc_camera_host *ici = to_soc_camera_host(icd->dev.parent);
	struct pxa_camera_dev *pcdev = ici->priv;

	/*
	 * We must pass NULL as dev pointer, then all pci_* dma operations
	 * transform to normal dma_* ones.
	 */
	videobuf_queue_sg_init(q, &pxa_videobuf_ops, NULL, &pcdev->lock,
				V4L2_BUF_TYPE_VIDEO_CAPTURE, V4L2_FIELD_NONE,
				sizeof(struct pxa_buffer), icd, &icd->video_lock);
}