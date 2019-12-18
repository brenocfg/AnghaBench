#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct videobuf_queue {int dummy; } ;
struct cx8800_fh {int type; struct videobuf_queue vbiq; struct videobuf_queue vidq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  V4L2_BUF_TYPE_VBI_CAPTURE 129 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE 128 

__attribute__((used)) static struct videobuf_queue* get_queue(struct cx8800_fh *fh)
{
	switch (fh->type) {
	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
		return &fh->vidq;
	case V4L2_BUF_TYPE_VBI_CAPTURE:
		return &fh->vbiq;
	default:
		BUG();
		return NULL;
	}
}