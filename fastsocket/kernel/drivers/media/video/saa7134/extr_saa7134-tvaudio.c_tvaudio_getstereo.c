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
struct saa7134_tvaudio {int mode; } ;
struct saa7134_dev {int dummy; } ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7134_AUDIO_STATUS ; 
 int /*<<< orphan*/  SAA7134_IDENT_SIF ; 
 int /*<<< orphan*/  SAA7134_NICAM_STATUS ; 
#define  TVAUDIO_FM_BG_STEREO 133 
#define  TVAUDIO_FM_K_STEREO 132 
#define  TVAUDIO_FM_MONO 131 
#define  TVAUDIO_FM_SAT_STEREO 130 
#define  TVAUDIO_NICAM_AM 129 
#define  TVAUDIO_NICAM_FM 128 
 int V4L2_TUNER_SUB_LANG1 ; 
 int V4L2_TUNER_SUB_LANG2 ; 
 int V4L2_TUNER_SUB_MONO ; 
 int V4L2_TUNER_SUB_STEREO ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int saa_readb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tvaudio_getstereo(struct saa7134_dev *dev, struct saa7134_tvaudio *audio)
{
	__u32 idp, nicam, nicam_status;
	int retval = -1;

	switch (audio->mode) {
	case TVAUDIO_FM_MONO:
		return V4L2_TUNER_SUB_MONO;
	case TVAUDIO_FM_K_STEREO:
	case TVAUDIO_FM_BG_STEREO:
		idp = (saa_readb(SAA7134_IDENT_SIF) & 0xe0) >> 5;
		dprintk("getstereo: fm/stereo: idp=0x%x\n",idp);
		if (0x03 == (idp & 0x03))
			retval = V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;
		else if (0x05 == (idp & 0x05))
			retval = V4L2_TUNER_SUB_MONO | V4L2_TUNER_SUB_STEREO;
		else if (0x01 == (idp & 0x01))
			retval = V4L2_TUNER_SUB_MONO;
		break;
	case TVAUDIO_FM_SAT_STEREO:
		/* not implemented (yet) */
		break;
	case TVAUDIO_NICAM_FM:
	case TVAUDIO_NICAM_AM:
		nicam = saa_readb(SAA7134_AUDIO_STATUS);
		dprintk("getstereo: nicam=0x%x\n",nicam);
		if (nicam & 0x1) {
			nicam_status = saa_readb(SAA7134_NICAM_STATUS);
			dprintk("getstereo: nicam_status=0x%x\n", nicam_status);

			switch (nicam_status & 0x03) {
			    case 0x01:
				retval = V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;
				break;
			    case 0x02:
				retval = V4L2_TUNER_SUB_MONO | V4L2_TUNER_SUB_STEREO;
				break;
			    default:
				retval = V4L2_TUNER_SUB_MONO;
			}
		} else {
			/* No nicam detected */
		}
		break;
	}
	if (retval != -1)
		dprintk("found audio subchannels:%s%s%s%s\n",
			(retval & V4L2_TUNER_SUB_MONO)   ? " mono"   : "",
			(retval & V4L2_TUNER_SUB_STEREO) ? " stereo" : "",
			(retval & V4L2_TUNER_SUB_LANG1)  ? " lang1"  : "",
			(retval & V4L2_TUNER_SUB_LANG2)  ? " lang2"  : "");
	return retval;
}