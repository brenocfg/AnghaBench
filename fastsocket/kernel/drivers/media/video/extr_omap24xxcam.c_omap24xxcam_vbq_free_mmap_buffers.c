#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct videobuf_queue {int /*<<< orphan*/  vb_lock; TYPE_2__** bufs; TYPE_1__* ops; } ;
struct TYPE_6__ {scalar_t__ memory; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* buf_release ) (struct videobuf_queue*,TYPE_2__*) ;} ;

/* Variables and functions */
 scalar_t__ V4L2_MEMORY_MMAP ; 
 int VIDEO_MAX_FRAME ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap24xxcam_vbq_free_mmap_buffer (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (struct videobuf_queue*,TYPE_2__*) ; 
 int /*<<< orphan*/  videobuf_mmap_free (struct videobuf_queue*) ; 

__attribute__((used)) static void omap24xxcam_vbq_free_mmap_buffers(struct videobuf_queue *vbq)
{
	int i;

	mutex_lock(&vbq->vb_lock);

	for (i = 0; i < VIDEO_MAX_FRAME; i++) {
		if (NULL == vbq->bufs[i])
			continue;
		if (V4L2_MEMORY_MMAP != vbq->bufs[i]->memory)
			continue;
		vbq->ops->buf_release(vbq, vbq->bufs[i]);
		omap24xxcam_vbq_free_mmap_buffer(vbq->bufs[i]);
		kfree(vbq->bufs[i]);
		vbq->bufs[i] = NULL;
	}

	mutex_unlock(&vbq->vb_lock);

	videobuf_mmap_free(vbq);
}