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
struct videobuf_queue {struct au0828_fh* priv_data; } ;
struct au0828_fh {TYPE_1__* dev; } ;
struct TYPE_2__ {int width; int height; } ;

/* Variables and functions */
 unsigned int AU0828_DEF_BUF ; 
 unsigned int AU0828_MIN_BUF ; 

__attribute__((used)) static int
buffer_setup(struct videobuf_queue *vq, unsigned int *count,
	     unsigned int *size)
{
	struct au0828_fh *fh = vq->priv_data;
	*size = (fh->dev->width * fh->dev->height * 16 + 7) >> 3;

	if (0 == *count)
		*count = AU0828_DEF_BUF;

	if (*count < AU0828_MIN_BUF)
		*count = AU0828_MIN_BUF;
	return 0;
}