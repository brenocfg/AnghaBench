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
struct TYPE_5__ {int offset; } ;
struct TYPE_6__ {int length; int index; TYPE_2__ m; int /*<<< orphan*/  memory; int /*<<< orphan*/  field; int /*<<< orphan*/  type; } ;
struct cafe_sio_buffer {TYPE_3__ v4lbuf; struct cafe_camera* cam; scalar_t__ mapcount; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  sizeimage; } ;
struct cafe_camera {TYPE_1__ pix_format; struct cafe_sio_buffer* sb_bufs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_MEMORY_MMAP ; 
 int /*<<< orphan*/ * vmalloc_user (int) ; 

__attribute__((used)) static int cafe_setup_siobuf(struct cafe_camera *cam, int index)
{
	struct cafe_sio_buffer *buf = cam->sb_bufs + index;

	INIT_LIST_HEAD(&buf->list);
	buf->v4lbuf.length = PAGE_ALIGN(cam->pix_format.sizeimage);
	buf->buffer = vmalloc_user(buf->v4lbuf.length);
	if (buf->buffer == NULL)
		return -ENOMEM;
	buf->mapcount = 0;
	buf->cam = cam;

	buf->v4lbuf.index = index;
	buf->v4lbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	buf->v4lbuf.field = V4L2_FIELD_NONE;
	buf->v4lbuf.memory = V4L2_MEMORY_MMAP;
	/*
	 * Offset: must be 32-bit even on a 64-bit system.  videobuf-dma-sg
	 * just uses the length times the index, but the spec warns
	 * against doing just that - vma merging problems.  So we
	 * leave a gap between each pair of buffers.
	 */
	buf->v4lbuf.m.offset = 2*index*buf->v4lbuf.length;
	return 0;
}