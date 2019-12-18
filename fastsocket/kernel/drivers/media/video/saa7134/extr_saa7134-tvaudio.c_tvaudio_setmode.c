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
struct saa7134_tvaudio {int carr1; int carr2; int mode; int /*<<< orphan*/  name; } ;
struct saa7134_dev {TYPE_1__* tvnorm; } ;
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7134_AUDIO_CLOCKS_PER_FIELD0 ; 
 int /*<<< orphan*/  SAA7134_AUDIO_CLOCKS_PER_FIELD1 ; 
 int /*<<< orphan*/  SAA7134_AUDIO_CLOCKS_PER_FIELD2 ; 
 int /*<<< orphan*/  SAA7134_DCXO_IDENT_CTRL ; 
 int /*<<< orphan*/  SAA7134_DEMODULATOR ; 
 int /*<<< orphan*/  SAA7134_FM_DEEMPHASIS ; 
 int /*<<< orphan*/  SAA7134_FM_DEMATRIX ; 
 int /*<<< orphan*/  SAA7134_NICAM_CONFIG ; 
 int /*<<< orphan*/  SAA7134_STEREO_DAC_OUTPUT_SELECT ; 
#define  TVAUDIO_FM_BG_STEREO 133 
#define  TVAUDIO_FM_K_STEREO 132 
#define  TVAUDIO_FM_MONO 131 
#define  TVAUDIO_FM_SAT_STEREO 130 
#define  TVAUDIO_NICAM_AM 129 
#define  TVAUDIO_NICAM_FM 128 
 scalar_t__ V4L2_STD_NTSC ; 
 int audio_clock_tweak ; 
 int /*<<< orphan*/  dprintk (char*,char*,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tvaudio_setcarrier (struct saa7134_dev*,int,int) ; 

__attribute__((used)) static void tvaudio_setmode(struct saa7134_dev *dev,
			    struct saa7134_tvaudio *audio,
			    char *note)
{
	int acpf, tweak = 0;

	if (dev->tvnorm->id == V4L2_STD_NTSC) {
		acpf = 0x19066;
	} else {
		acpf = 0x1e000;
	}
	if (audio_clock_tweak > -1024 && audio_clock_tweak < 1024)
		tweak = audio_clock_tweak;

	if (note)
		dprintk("tvaudio_setmode: %s %s [%d.%03d/%d.%03d MHz] acpf=%d%+d\n",
			note,audio->name,
			audio->carr1 / 1000, audio->carr1 % 1000,
			audio->carr2 / 1000, audio->carr2 % 1000,
			acpf, tweak);

	acpf += tweak;
	saa_writeb(SAA7134_AUDIO_CLOCKS_PER_FIELD0, (acpf & 0x0000ff) >> 0);
	saa_writeb(SAA7134_AUDIO_CLOCKS_PER_FIELD1, (acpf & 0x00ff00) >> 8);
	saa_writeb(SAA7134_AUDIO_CLOCKS_PER_FIELD2, (acpf & 0x030000) >> 16);
	tvaudio_setcarrier(dev,audio->carr1,audio->carr2);

	switch (audio->mode) {
	case TVAUDIO_FM_MONO:
	case TVAUDIO_FM_BG_STEREO:
		saa_writeb(SAA7134_DEMODULATOR,               0x00);
		saa_writeb(SAA7134_DCXO_IDENT_CTRL,           0x00);
		saa_writeb(SAA7134_FM_DEEMPHASIS,             0x22);
		saa_writeb(SAA7134_FM_DEMATRIX,               0x80);
		saa_writeb(SAA7134_STEREO_DAC_OUTPUT_SELECT,  0xa0);
		break;
	case TVAUDIO_FM_K_STEREO:
		saa_writeb(SAA7134_DEMODULATOR,               0x00);
		saa_writeb(SAA7134_DCXO_IDENT_CTRL,           0x01);
		saa_writeb(SAA7134_FM_DEEMPHASIS,             0x22);
		saa_writeb(SAA7134_FM_DEMATRIX,               0x80);
		saa_writeb(SAA7134_STEREO_DAC_OUTPUT_SELECT,  0xa0);
		break;
	case TVAUDIO_NICAM_FM:
		saa_writeb(SAA7134_DEMODULATOR,               0x10);
		saa_writeb(SAA7134_DCXO_IDENT_CTRL,           0x00);
		saa_writeb(SAA7134_FM_DEEMPHASIS,             0x44);
		saa_writeb(SAA7134_STEREO_DAC_OUTPUT_SELECT,  0xa1);
		saa_writeb(SAA7134_NICAM_CONFIG,              0x00);
		break;
	case TVAUDIO_NICAM_AM:
		saa_writeb(SAA7134_DEMODULATOR,               0x12);
		saa_writeb(SAA7134_DCXO_IDENT_CTRL,           0x00);
		saa_writeb(SAA7134_FM_DEEMPHASIS,             0x44);
		saa_writeb(SAA7134_STEREO_DAC_OUTPUT_SELECT,  0xa1);
		saa_writeb(SAA7134_NICAM_CONFIG,              0x00);
		break;
	case TVAUDIO_FM_SAT_STEREO:
		/* not implemented (yet) */
		break;
	}
}