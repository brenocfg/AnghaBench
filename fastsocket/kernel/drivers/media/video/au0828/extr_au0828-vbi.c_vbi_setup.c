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
struct videobuf_queue {struct au0828_fh* priv_data; } ;
struct au0828_fh {struct au0828_dev* dev; } ;
struct au0828_dev {int vbi_width; int vbi_height; } ;

/* Variables and functions */
 unsigned int vbibufs ; 

__attribute__((used)) static int
vbi_setup(struct videobuf_queue *q, unsigned int *count, unsigned int *size)
{
	struct au0828_fh     *fh  = q->priv_data;
	struct au0828_dev    *dev = fh->dev;

	*size = dev->vbi_width * dev->vbi_height * 2;

	if (0 == *count)
		*count = vbibufs;
	if (*count < 2)
		*count = 2;
	if (*count > 32)
		*count = 32;
	return 0;
}