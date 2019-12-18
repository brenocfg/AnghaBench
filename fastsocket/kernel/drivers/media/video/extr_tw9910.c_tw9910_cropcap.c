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
struct v4l2_subdev {int dummy; } ;
struct TYPE_6__ {int numerator; int denominator; } ;
struct TYPE_5__ {int width; int height; scalar_t__ top; scalar_t__ left; } ;
struct TYPE_4__ {int width; int height; scalar_t__ top; scalar_t__ left; } ;
struct v4l2_cropcap {TYPE_3__ pixelaspect; int /*<<< orphan*/  type; TYPE_2__ defrect; TYPE_1__ bounds; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 

__attribute__((used)) static int tw9910_cropcap(struct v4l2_subdev *sd, struct v4l2_cropcap *a)
{
	a->bounds.left			= 0;
	a->bounds.top			= 0;
	a->bounds.width			= 768;
	a->bounds.height		= 576;
	a->defrect.left			= 0;
	a->defrect.top			= 0;
	a->defrect.width		= 640;
	a->defrect.height		= 480;
	a->type				= V4L2_BUF_TYPE_VIDEO_CAPTURE;
	a->pixelaspect.numerator	= 1;
	a->pixelaspect.denominator	= 1;

	return 0;
}