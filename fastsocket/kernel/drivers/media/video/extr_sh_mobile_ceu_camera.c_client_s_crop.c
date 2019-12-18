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
struct v4l2_subdev {TYPE_1__* v4l2_dev; } ;
struct v4l2_rect {unsigned int width; unsigned int height; scalar_t__ left; scalar_t__ top; } ;
struct v4l2_cropcap {struct v4l2_rect bounds; struct v4l2_rect c; } ;
struct v4l2_crop {struct v4l2_rect bounds; struct v4l2_rect c; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int client_g_rect (struct v4l2_subdev*,struct v4l2_rect*) ; 
 int /*<<< orphan*/  cropcap ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int,unsigned int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_geo (struct device*,char*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,...) ; 
 scalar_t__ is_inside (struct v4l2_rect*,struct v4l2_rect*) ; 
 scalar_t__ is_smaller (struct v4l2_rect*,struct v4l2_rect*) ; 
 unsigned int max (unsigned int,int) ; 
 int /*<<< orphan*/  memcmp (struct v4l2_rect*,struct v4l2_rect*,int) ; 
 int /*<<< orphan*/  s_crop ; 
 int /*<<< orphan*/  soc_camera_limit_side (scalar_t__*,unsigned int*,scalar_t__,int,unsigned int) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_cropcap*) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int client_s_crop(struct v4l2_subdev *sd, struct v4l2_crop *crop,
			 struct v4l2_crop *cam_crop)
{
	struct v4l2_rect *rect = &crop->c, *cam_rect = &cam_crop->c;
	struct device *dev = sd->v4l2_dev->dev;
	struct v4l2_cropcap cap;
	int ret;
	unsigned int width, height;

	v4l2_subdev_call(sd, video, s_crop, crop);
	ret = client_g_rect(sd, cam_rect);
	if (ret < 0)
		return ret;

	/*
	 * Now cam_crop contains the current camera input rectangle, and it must
	 * be within camera cropcap bounds
	 */
	if (!memcmp(rect, cam_rect, sizeof(*rect))) {
		/* Even if camera S_CROP failed, but camera rectangle matches */
		dev_dbg(dev, "Camera S_CROP successful for %ux%u@%u:%u\n",
			rect->width, rect->height, rect->left, rect->top);
		return 0;
	}

	/* Try to fix cropping, that camera hasn't managed to set */
	dev_geo(dev, "Fix camera S_CROP for %ux%u@%u:%u to %ux%u@%u:%u\n",
		cam_rect->width, cam_rect->height,
		cam_rect->left, cam_rect->top,
		rect->width, rect->height, rect->left, rect->top);

	/* We need sensor maximum rectangle */
	ret = v4l2_subdev_call(sd, video, cropcap, &cap);
	if (ret < 0)
		return ret;

	soc_camera_limit_side(&rect->left, &rect->width, cap.bounds.left, 2,
			      cap.bounds.width);
	soc_camera_limit_side(&rect->top, &rect->height, cap.bounds.top, 4,
			      cap.bounds.height);

	/*
	 * Popular special case - some cameras can only handle fixed sizes like
	 * QVGA, VGA,... Take care to avoid infinite loop.
	 */
	width = max(cam_rect->width, 2);
	height = max(cam_rect->height, 2);

	while (!ret && (is_smaller(cam_rect, rect) ||
			is_inside(cam_rect, rect)) &&
	       (cap.bounds.width > width || cap.bounds.height > height)) {

		width *= 2;
		height *= 2;

		cam_rect->width = width;
		cam_rect->height = height;

		/*
		 * We do not know what capabilities the camera has to set up
		 * left and top borders. We could try to be smarter in iterating
		 * them, e.g., if camera current left is to the right of the
		 * target left, set it to the middle point between the current
		 * left and minimum left. But that would add too much
		 * complexity: we would have to iterate each border separately.
		 */
		if (cam_rect->left > rect->left)
			cam_rect->left = cap.bounds.left;

		if (cam_rect->left + cam_rect->width < rect->left + rect->width)
			cam_rect->width = rect->left + rect->width -
				cam_rect->left;

		if (cam_rect->top > rect->top)
			cam_rect->top = cap.bounds.top;

		if (cam_rect->top + cam_rect->height < rect->top + rect->height)
			cam_rect->height = rect->top + rect->height -
				cam_rect->top;

		v4l2_subdev_call(sd, video, s_crop, cam_crop);
		ret = client_g_rect(sd, cam_rect);
		dev_geo(dev, "Camera S_CROP %d for %ux%u@%u:%u\n", ret,
			cam_rect->width, cam_rect->height,
			cam_rect->left, cam_rect->top);
	}

	/* S_CROP must not modify the rectangle */
	if (is_smaller(cam_rect, rect) || is_inside(cam_rect, rect)) {
		/*
		 * The camera failed to configure a suitable cropping,
		 * we cannot use the current rectangle, set to max
		 */
		*cam_rect = cap.bounds;
		v4l2_subdev_call(sd, video, s_crop, cam_crop);
		ret = client_g_rect(sd, cam_rect);
		dev_geo(dev, "Camera S_CROP %d for max %ux%u@%u:%u\n", ret,
			cam_rect->width, cam_rect->height,
			cam_rect->left, cam_rect->top);
	}

	return ret;
}