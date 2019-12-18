#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct videobuf_queue {struct omap24xxcam_fh* priv_data; } ;
struct TYPE_3__ {unsigned int sizeimage; } ;
struct omap24xxcam_fh {TYPE_2__* cam; TYPE_1__ pix; } ;
struct TYPE_4__ {unsigned int capture_mem; } ;

/* Variables and functions */
 unsigned int VIDEO_MAX_FRAME ; 

__attribute__((used)) static int omap24xxcam_vbq_setup(struct videobuf_queue *vbq, unsigned int *cnt,
				 unsigned int *size)
{
	struct omap24xxcam_fh *fh = vbq->priv_data;

	if (*cnt <= 0)
		*cnt = VIDEO_MAX_FRAME;	/* supply a default number of buffers */

	if (*cnt > VIDEO_MAX_FRAME)
		*cnt = VIDEO_MAX_FRAME;

	*size = fh->pix.sizeimage;

	/* accessing fh->cam->capture_mem is ok, it's constant */
	while (*size * *cnt > fh->cam->capture_mem)
		(*cnt)--;

	return 0;
}