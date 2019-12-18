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
struct v4l2_tuner {scalar_t__ index; int signal; int /*<<< orphan*/  rxsubchans; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct saa7134_fh {struct saa7134_dev* dev; } ;
struct saa7134_dev {TYPE_1__* input; } ;
struct file {struct saa7134_fh* private_data; } ;
struct TYPE_2__ {scalar_t__ amux; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TV ; 
 int /*<<< orphan*/  V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_MONO ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_STEREO ; 
 int /*<<< orphan*/  g_tuner ; 
 int /*<<< orphan*/  memset (struct v4l2_tuner*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  saa_call_all (struct saa7134_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_tuner*) ; 
 int saa_readb (int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tuner ; 

__attribute__((used)) static int radio_g_tuner(struct file *file, void *priv,
					struct v4l2_tuner *t)
{
	struct saa7134_fh *fh = file->private_data;
	struct saa7134_dev *dev = fh->dev;

	if (0 != t->index)
		return -EINVAL;

	memset(t, 0, sizeof(*t));
	strcpy(t->name, "Radio");
	t->type = V4L2_TUNER_RADIO;

	saa_call_all(dev, tuner, g_tuner, t);
	if (dev->input->amux == TV) {
		t->signal = 0xf800 - ((saa_readb(0x581) & 0x1f) << 11);
		t->rxsubchans = (saa_readb(0x529) & 0x08) ?
				V4L2_TUNER_SUB_STEREO : V4L2_TUNER_SUB_MONO;
	}
	return 0;
}