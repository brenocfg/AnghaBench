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
struct TYPE_4__ {int is_50hz; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct cx8802_dev {TYPE_2__ params; TYPE_1__* core; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_3__ {int tvnorm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_ENC_SET_FRAME_SIZE ; 
 int V4L2_STD_625_50 ; 
 int /*<<< orphan*/  blackbird_api_cmd (struct cx8802_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blackbird_mbox_func ; 
 int /*<<< orphan*/  cx2341x_update (struct cx8802_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void blackbird_codec_settings(struct cx8802_dev *dev)
{
	/* assign frame size */
	blackbird_api_cmd(dev, CX2341X_ENC_SET_FRAME_SIZE, 2, 0,
				dev->height, dev->width);

	dev->params.width = dev->width;
	dev->params.height = dev->height;
	dev->params.is_50hz = (dev->core->tvnorm & V4L2_STD_625_50) != 0;

	cx2341x_update(dev, blackbird_mbox_func, NULL, &dev->params);
}