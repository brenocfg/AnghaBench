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
typedef  unsigned int u16 ;
struct ac97_mixer_hw {unsigned int scale; int /*<<< orphan*/  offset; } ;
struct ac97_codec {int bit_resolution; int (* codec_read ) (struct ac97_codec*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* codec_write ) (struct ac97_codec*,int /*<<< orphan*/ ,unsigned int) ;scalar_t__ id; } ;

/* Variables and functions */
 unsigned int AC97_MUTE ; 
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
 int /*<<< orphan*/  printk (char*,unsigned int,...) ; 
 int stub1 (struct ac97_codec*,int /*<<< orphan*/ ) ; 
 int stub2 (struct ac97_codec*,int /*<<< orphan*/ ) ; 
 int stub3 (struct ac97_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct ac97_codec*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int stub5 (struct ac97_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ac97_write_mixer(struct ac97_codec *codec, int oss_channel,
		      unsigned int left, unsigned int right)
{
	u16 val = 0;
	int scale;
	struct ac97_mixer_hw *mh = &ac97_hw[oss_channel];

#ifdef DEBUG
	printk("ac97_codec: wrote OSS mixer %2d (%s ac97 register 0x%02x), "
	       "left vol:%2d, right vol:%2d:",
	       oss_channel, codec->id ? "Secondary" : "Primary",
	       mh->offset, left, right);
#endif

	if (AC97_STEREO_MASK & (1 << oss_channel)) {
		/* stereo mixers */
		if (left == 0 && right == 0) {
			val = AC97_MUTE;
		} else {
			if (oss_channel == SOUND_MIXER_IGAIN) {
				right = (right * mh->scale) / 100;
				left = (left * mh->scale) / 100;
				if (right >= mh->scale)
					right = mh->scale-1;
				if (left >= mh->scale)
					left = mh->scale-1;
			} else {
				/* these may have 5 or 6 bit resolution */
				if (oss_channel == SOUND_MIXER_VOLUME ||
				    oss_channel == SOUND_MIXER_ALTPCM)
					scale = (1 << codec->bit_resolution);
				else
					scale = mh->scale;

				right = ((100 - right) * scale) / 100;
				left = ((100 - left) * scale) / 100;
				if (right >= scale)
					right = scale-1;
				if (left >= scale)
					left = scale-1;
			}
			val = (left << 8) | right;
		}
	} else if (oss_channel == SOUND_MIXER_BASS) {
		val = codec->codec_read(codec , mh->offset) & ~0x0f00;
		left = ((100 - left) * mh->scale) / 100;
		if (left >= mh->scale)
			left = mh->scale-1;
		val |= (left << 8) & 0x0e00;
	} else if (oss_channel == SOUND_MIXER_TREBLE) {
		val = codec->codec_read(codec , mh->offset) & ~0x000f;
		left = ((100 - left) * mh->scale) / 100;
		if (left >= mh->scale)
			left = mh->scale-1;
		val |= left & 0x000e;
	} else if(left == 0) {
		val = AC97_MUTE;
	} else if (oss_channel == SOUND_MIXER_SPEAKER) {
		left = ((100 - left) * mh->scale) / 100;
		if (left >= mh->scale)
			left = mh->scale-1;
		val = left << 1;
	} else if (oss_channel == SOUND_MIXER_PHONEIN) {
		left = ((100 - left) * mh->scale) / 100;
		if (left >= mh->scale)
			left = mh->scale-1;
		val = left;
	} else if (oss_channel == SOUND_MIXER_PHONEOUT) {
		scale = (1 << codec->bit_resolution);
		left = ((100 - left) * scale) / 100;
		if (left >= mh->scale)
			left = mh->scale-1;
		val = left;
	} else if (oss_channel == SOUND_MIXER_MIC) {
		val = codec->codec_read(codec , mh->offset) & ~0x801f;
		left = ((100 - left) * mh->scale) / 100;
		if (left >= mh->scale)
			left = mh->scale-1;
		val |= left;
		/*  the low bit is optional in the tone sliders and masking
		    it lets us avoid the 0xf 'bypass'.. */
	}
#ifdef DEBUG
	printk(" 0x%04x", val);
#endif

	codec->codec_write(codec, mh->offset, val);

#ifdef DEBUG
	val = codec->codec_read(codec, mh->offset);
	printk(" -> 0x%04x\n", val);
#endif
}