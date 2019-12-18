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
struct v4l2_jpegcompression {int quality; int jpeg_markers; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int V4L2_JPEG_MARKER_DHT ; 
 int V4L2_JPEG_MARKER_DQT ; 
 int /*<<< orphan*/  memset (struct v4l2_jpegcompression*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_g_jpegcomp(struct file *file, void *priv,
			 struct v4l2_jpegcompression *params)
{
	memset(params, 0, sizeof(*params));
	params->quality = 50; /* ?? */
	params->jpeg_markers = V4L2_JPEG_MARKER_DHT |
				V4L2_JPEG_MARKER_DQT;

	return 0;
}