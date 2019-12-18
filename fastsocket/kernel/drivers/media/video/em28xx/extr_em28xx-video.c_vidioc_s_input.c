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
struct file {int dummy; } ;
struct em28xx_fh {struct em28xx* dev; } ;
struct em28xx {unsigned int ctl_input; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* INPUT (unsigned int) ; 
 unsigned int MAX_EM28XX_INPUT ; 
 int check_dev (struct em28xx*) ; 
 int /*<<< orphan*/  video_mux (struct em28xx*,unsigned int) ; 

__attribute__((used)) static int vidioc_s_input(struct file *file, void *priv, unsigned int i)
{
	struct em28xx_fh   *fh  = priv;
	struct em28xx      *dev = fh->dev;
	int                rc;

	rc = check_dev(dev);
	if (rc < 0)
		return rc;

	if (i >= MAX_EM28XX_INPUT)
		return -EINVAL;
	if (0 == INPUT(i)->type)
		return -EINVAL;

	dev->ctl_input = i;

	video_mux(dev, dev->ctl_input);
	return 0;
}