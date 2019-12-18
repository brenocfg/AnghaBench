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
struct cx231xx_fh {scalar_t__ type; scalar_t__ stream_on; struct cx231xx* dev; } ;
struct cx231xx {scalar_t__ vbi_stream_on; scalar_t__ stream_on; } ;

/* Variables and functions */
 scalar_t__ V4L2_BUF_TYPE_VBI_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 

__attribute__((used)) static void res_free(struct cx231xx_fh *fh)
{
	struct cx231xx *dev = fh->dev;

	fh->stream_on = 0;

	if (fh->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		dev->stream_on = 0;
	if (fh->type == V4L2_BUF_TYPE_VBI_CAPTURE)
		dev->vbi_stream_on = 0;
}