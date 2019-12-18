#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct saa7146_vv {TYPE_4__* ov_fmt; } ;
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  top; int /*<<< orphan*/  left; int /*<<< orphan*/  width; } ;
struct TYPE_6__ {int /*<<< orphan*/  field; TYPE_1__ w; } ;
struct TYPE_7__ {TYPE_2__ win; } ;
struct saa7146_fh {TYPE_3__ ov; struct saa7146_dev* dev; } ;
struct saa7146_dev {struct saa7146_vv* vv_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  trans; int /*<<< orphan*/  pixelformat; } ;

/* Variables and functions */
 int MASK_06 ; 
 int MASK_22 ; 
 int /*<<< orphan*/  MC1 ; 
 int /*<<< orphan*/  saa7146_set_clipping_rect (struct saa7146_fh*) ; 
 int /*<<< orphan*/  saa7146_set_output_format (struct saa7146_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_set_position (struct saa7146_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_set_window (struct saa7146_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_write (struct saa7146_dev*,int /*<<< orphan*/ ,int) ; 

int saa7146_enable_overlay(struct saa7146_fh *fh)
{
	struct saa7146_dev *dev = fh->dev;
	struct saa7146_vv *vv = dev->vv_data;

	saa7146_set_window(dev, fh->ov.win.w.width, fh->ov.win.w.height, fh->ov.win.field);
	saa7146_set_position(dev, fh->ov.win.w.left, fh->ov.win.w.top, fh->ov.win.w.height, fh->ov.win.field, vv->ov_fmt->pixelformat);
	saa7146_set_output_format(dev, vv->ov_fmt->trans);
	saa7146_set_clipping_rect(fh);

	/* enable video dma1 */
	saa7146_write(dev, MC1, (MASK_06 | MASK_22));
	return 0;
}