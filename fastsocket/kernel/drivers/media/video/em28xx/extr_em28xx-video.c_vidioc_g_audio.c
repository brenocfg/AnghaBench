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
struct v4l2_audio {int /*<<< orphan*/  capability; int /*<<< orphan*/  index; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;
struct em28xx_fh {struct em28xx* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  has_audio; } ;
struct em28xx {int /*<<< orphan*/  ctl_ainput; TYPE_1__ audio_mode; } ;

/* Variables and functions */
 int EINVAL ; 
#define  EM28XX_AMUX_AUX 135 
#define  EM28XX_AMUX_CD 134 
#define  EM28XX_AMUX_LINE_IN 133 
#define  EM28XX_AMUX_MIC 132 
#define  EM28XX_AMUX_PCM_OUT 131 
#define  EM28XX_AMUX_PHONE 130 
#define  EM28XX_AMUX_VIDEO 129 
#define  EM28XX_AMUX_VIDEO2 128 
 int /*<<< orphan*/  V4L2_AUDCAP_STEREO ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int vidioc_g_audio(struct file *file, void *priv, struct v4l2_audio *a)
{
	struct em28xx_fh   *fh    = priv;
	struct em28xx      *dev   = fh->dev;

	if (!dev->audio_mode.has_audio)
		return -EINVAL;

	switch (a->index) {
	case EM28XX_AMUX_VIDEO:
		strcpy(a->name, "Television");
		break;
	case EM28XX_AMUX_LINE_IN:
		strcpy(a->name, "Line In");
		break;
	case EM28XX_AMUX_VIDEO2:
		strcpy(a->name, "Television alt");
		break;
	case EM28XX_AMUX_PHONE:
		strcpy(a->name, "Phone");
		break;
	case EM28XX_AMUX_MIC:
		strcpy(a->name, "Mic");
		break;
	case EM28XX_AMUX_CD:
		strcpy(a->name, "CD");
		break;
	case EM28XX_AMUX_AUX:
		strcpy(a->name, "Aux");
		break;
	case EM28XX_AMUX_PCM_OUT:
		strcpy(a->name, "PCM");
		break;
	default:
		return -EINVAL;
	}

	a->index = dev->ctl_ainput;
	a->capability = V4L2_AUDCAP_STEREO;

	return 0;
}