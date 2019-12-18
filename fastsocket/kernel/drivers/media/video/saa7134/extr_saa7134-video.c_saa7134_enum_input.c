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
struct v4l2_input {unsigned int index; int audioset; int /*<<< orphan*/  std; int /*<<< orphan*/  status; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct saa7134_fh {struct saa7134_dev* dev; } ;
struct saa7134_dev {unsigned int ctl_input; } ;
struct file {int dummy; } ;
struct TYPE_2__ {scalar_t__ tv; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int SAA7134_INPUT_MAX ; 
 int /*<<< orphan*/  SAA7134_NORMS ; 
 int /*<<< orphan*/  SAA7134_STATUS_VIDEO1 ; 
 int /*<<< orphan*/  SAA7134_STATUS_VIDEO2 ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_TUNER ; 
 int /*<<< orphan*/  V4L2_IN_ST_MACROVISION ; 
 int /*<<< orphan*/  V4L2_IN_ST_NO_H_LOCK ; 
 int /*<<< orphan*/  V4L2_IN_ST_NO_SYNC ; 
 TYPE_1__ card_in (struct saa7134_dev*,unsigned int) ; 
 int saa_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int saa7134_enum_input(struct file *file, void *priv,
					struct v4l2_input *i)
{
	struct saa7134_fh *fh = priv;
	struct saa7134_dev *dev = fh->dev;
	unsigned int n;

	n = i->index;
	if (n >= SAA7134_INPUT_MAX)
		return -EINVAL;
	if (NULL == card_in(dev, i->index).name)
		return -EINVAL;
	i->index = n;
	i->type  = V4L2_INPUT_TYPE_CAMERA;
	strcpy(i->name, card_in(dev, n).name);
	if (card_in(dev, n).tv)
		i->type = V4L2_INPUT_TYPE_TUNER;
	i->audioset = 1;
	if (n == dev->ctl_input) {
		int v1 = saa_readb(SAA7134_STATUS_VIDEO1);
		int v2 = saa_readb(SAA7134_STATUS_VIDEO2);

		if (0 != (v1 & 0x40))
			i->status |= V4L2_IN_ST_NO_H_LOCK;
		if (0 != (v2 & 0x40))
			i->status |= V4L2_IN_ST_NO_SYNC;
		if (0 != (v2 & 0x0e))
			i->status |= V4L2_IN_ST_MACROVISION;
	}
	i->std = SAA7134_NORMS;
	return 0;
}