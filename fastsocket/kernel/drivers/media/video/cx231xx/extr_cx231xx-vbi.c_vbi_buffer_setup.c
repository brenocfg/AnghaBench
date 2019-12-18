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
typedef  int u32 ;
struct videobuf_queue {struct cx231xx_fh* priv_data; } ;
struct cx231xx_fh {struct cx231xx* dev; } ;
struct cx231xx {int norm; int width; } ;

/* Variables and functions */
 unsigned int CX231XX_DEF_VBI_BUF ; 
 unsigned int CX231XX_MIN_BUF ; 
 int NTSC_VBI_LINES ; 
 int PAL_VBI_LINES ; 
 int V4L2_STD_625_50 ; 

__attribute__((used)) static int
vbi_buffer_setup(struct videobuf_queue *vq, unsigned int *count,
		 unsigned int *size)
{
	struct cx231xx_fh *fh = vq->priv_data;
	struct cx231xx *dev = fh->dev;
	u32 height = 0;

	height = ((dev->norm & V4L2_STD_625_50) ?
		  PAL_VBI_LINES : NTSC_VBI_LINES);

	*size = (dev->width * height * 2 * 2);
	if (0 == *count)
		*count = CX231XX_DEF_VBI_BUF;

	if (*count < CX231XX_MIN_BUF)
		*count = CX231XX_MIN_BUF;

	return 0;
}