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
typedef  int u16 ;
struct ac97_mixer_hw {int scale; int /*<<< orphan*/  offset; } ;
struct ac97_codec {int (* codec_read ) (struct ac97_codec*,int /*<<< orphan*/ ) ;int bit_resolution; scalar_t__ id; } ;

/* Variables and functions */
 int AC97_MUTE ; 
 int AC97_STEREO_MASK ; 
 int SOUND_MIXER_ALTPCM ; 
 int SOUND_MIXER_BASS ; 
 int SOUND_MIXER_IGAIN ; 
 int SOUND_MIXER_MIC ; 
 int SOUND_MIXER_PHONEIN ; 
 int SOUND_MIXER_PHONEOUT ; 
 int SOUND_MIXER_SPEAKER ; 
 int SOUND_MIXER_TREBLE ; 
 int SOUND_MIXER_VOLUME ; 
 struct ac97_mixer_hw* ac97_hw ; 
 int /*<<< orphan*/  printk (char*,int,char*,int /*<<< orphan*/ ,int,int) ; 
 int stub1 (struct ac97_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ac97_read_mixer(struct ac97_codec *codec, int oss_channel) 
{
	u16 val;
	int ret = 0;
	int scale;
	struct ac97_mixer_hw *mh = &ac97_hw[oss_channel];

	val = codec->codec_read(codec , mh->offset);

	if (val & AC97_MUTE) {
		ret = 0;
	} else if (AC97_STEREO_MASK & (1 << oss_channel)) {
		/* nice stereo mixers .. */
		int left,right;

		left = (val >> 8)  & 0x7f;
		right = val  & 0x7f;

		if (oss_channel == SOUND_MIXER_IGAIN) {
			right = (right * 100) / mh->scale;
			left = (left * 100) / mh->scale;
		} else {
			/* these may have 5 or 6 bit resolution */
			if(oss_channel == SOUND_MIXER_VOLUME || oss_channel == SOUND_MIXER_ALTPCM)
				scale = (1 << codec->bit_resolution);
			else
				scale = mh->scale;

			right = 100 - ((right * 100) / scale);
			left = 100 - ((left * 100) / scale);
		}
		ret = left | (right << 8);
	} else if (oss_channel == SOUND_MIXER_SPEAKER) {
		ret = 100 - ((((val & 0x1e)>>1) * 100) / mh->scale);
	} else if (oss_channel == SOUND_MIXER_PHONEIN) {
		ret = 100 - (((val & 0x1f) * 100) / mh->scale);
	} else if (oss_channel == SOUND_MIXER_PHONEOUT) {
		scale = (1 << codec->bit_resolution);
		ret = 100 - (((val & 0x1f) * 100) / scale);
	} else if (oss_channel == SOUND_MIXER_MIC) {
		ret = 100 - (((val & 0x1f) * 100) / mh->scale);
		/*  the low bit is optional in the tone sliders and masking
		    it lets us avoid the 0xf 'bypass'.. */
	} else if (oss_channel == SOUND_MIXER_BASS) {
		ret = 100 - ((((val >> 8) & 0xe) * 100) / mh->scale);
	} else if (oss_channel == SOUND_MIXER_TREBLE) {
		ret = 100 - (((val & 0xe) * 100) / mh->scale);
	}

#ifdef DEBUG
	printk("ac97_codec: read OSS mixer %2d (%s ac97 register 0x%02x), "
	       "0x%04x -> 0x%04x\n",
	       oss_channel, codec->id ? "Secondary" : "Primary",
	       mh->offset, val, ret);
#endif

	return ret;
}