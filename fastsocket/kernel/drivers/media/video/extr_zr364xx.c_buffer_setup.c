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
struct zr364xx_camera {int width; int height; TYPE_1__* fmt; } ;
struct videobuf_queue {struct zr364xx_camera* priv_data; } ;
struct TYPE_2__ {int depth; } ;

/* Variables and functions */
 int ZR364XX_DEF_BUFS ; 

__attribute__((used)) static int buffer_setup(struct videobuf_queue *vq, unsigned int *count,
			unsigned int *size)
{
	struct zr364xx_camera *cam = vq->priv_data;

	*size = cam->width * cam->height * (cam->fmt->depth >> 3);

	if (*count == 0)
		*count = ZR364XX_DEF_BUFS;

	if (*size * *count > ZR364XX_DEF_BUFS * 1024 * 1024)
		*count = (ZR364XX_DEF_BUFS * 1024 * 1024) / *size;

	return 0;
}