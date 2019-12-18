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
struct v4l2_tuner {scalar_t__ index; int capability; int rangehigh; int signal; int /*<<< orphan*/  rxsubchans; int /*<<< orphan*/  audmode; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct saa7134_fh {struct saa7134_dev* dev; } ;
struct saa7134_dev {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * name; scalar_t__ tv; } ;

/* Variables and functions */
 int EINVAL ; 
 int SAA7134_INPUT_MAX ; 
 int /*<<< orphan*/  SAA7134_STATUS_VIDEO1 ; 
 int /*<<< orphan*/  V4L2_TUNER_ANALOG_TV ; 
 int V4L2_TUNER_CAP_LANG1 ; 
 int V4L2_TUNER_CAP_LANG2 ; 
 int V4L2_TUNER_CAP_NORM ; 
 int V4L2_TUNER_CAP_STEREO ; 
 TYPE_1__ card_in (struct saa7134_dev*,int) ; 
 int /*<<< orphan*/  memset (struct v4l2_tuner*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  saa7134_tvaudio_getstereo (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa7134_tvaudio_rx2mode (int /*<<< orphan*/ ) ; 
 int saa_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int saa7134_g_tuner(struct file *file, void *priv,
					struct v4l2_tuner *t)
{
	struct saa7134_fh *fh = priv;
	struct saa7134_dev *dev = fh->dev;
	int n;

	if (0 != t->index)
		return -EINVAL;
	memset(t, 0, sizeof(*t));
	for (n = 0; n < SAA7134_INPUT_MAX; n++) {
		if (card_in(dev, n).tv)
			break;
	}
	if (n == SAA7134_INPUT_MAX)
		return -EINVAL;
	if (NULL != card_in(dev, n).name) {
		strcpy(t->name, "Television");
		t->type = V4L2_TUNER_ANALOG_TV;
		t->capability = V4L2_TUNER_CAP_NORM |
			V4L2_TUNER_CAP_STEREO |
			V4L2_TUNER_CAP_LANG1 |
			V4L2_TUNER_CAP_LANG2;
		t->rangehigh = 0xffffffffUL;
		t->rxsubchans = saa7134_tvaudio_getstereo(dev);
		t->audmode = saa7134_tvaudio_rx2mode(t->rxsubchans);
	}
	if (0 != (saa_readb(SAA7134_STATUS_VIDEO1) & 0x03))
		t->signal = 0xffff;
	return 0;
}