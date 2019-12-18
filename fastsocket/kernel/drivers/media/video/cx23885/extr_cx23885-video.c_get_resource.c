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
struct cx23885_fh {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int RESOURCE_VBI ; 
 int RESOURCE_VIDEO ; 
#define  V4L2_BUF_TYPE_VBI_CAPTURE 129 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE 128 

__attribute__((used)) static int get_resource(struct cx23885_fh *fh)
{
	switch (fh->type) {
	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
		return RESOURCE_VIDEO;
	case V4L2_BUF_TYPE_VBI_CAPTURE:
		return RESOURCE_VBI;
	default:
		BUG();
		return 0;
	}
}