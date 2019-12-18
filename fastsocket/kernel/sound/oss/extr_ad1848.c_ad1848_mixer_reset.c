#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* chip_name; int* mixer_reroute; int model; int supported_devices; int orig_devices; int* levels; int mixer_output_port; int /*<<< orphan*/  lock; int /*<<< orphan*/  supported_rec_devices; int /*<<< orphan*/  orig_rec_devices; int /*<<< orphan*/ * mix_devices; } ;
typedef  TYPE_1__ ad1848_info ;

/* Variables and functions */
 int AUDIO_HEADPHONE ; 
 int AUDIO_LINE_OUT ; 
 int AUDIO_SPEAKER ; 
 int C930_MIXER_DEVICES ; 
#define  MD_1845 139 
#define  MD_1845_SSCAPE 138 
#define  MD_1848 137 
#define  MD_4231 136 
#define  MD_4231A 135 
#define  MD_4232 134 
#define  MD_4235 133 
#define  MD_4236 132 
#define  MD_4239 131 
#define  MD_42xB 130 
#define  MD_C930 129 
#define  MD_IWAVE 128 
 int MODE1_MIXER_DEVICES ; 
 int /*<<< orphan*/  MODE1_REC_DEVICES ; 
 int MODE2_MIXER_DEVICES ; 
 void* MODE3_MIXER_DEVICES ; 
 int /*<<< orphan*/  SOUND_MASK_MIC ; 
 int SOUND_MIXER_NRDEVICES ; 
 int SPRO_MIXER_DEVICES ; 
 int /*<<< orphan*/  SPRO_REC_DEVICES ; 
 int /*<<< orphan*/ * ad1848_mix_devices ; 
 int /*<<< orphan*/  ad1848_mixer_set (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ad1848_set_recmask (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int ad_read (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ad_write (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/ * c930_mix_devices ; 
 int /*<<< orphan*/ * cs42xb_mix_devices ; 
 int /*<<< orphan*/  default_mixer_levels ; 
 int /*<<< orphan*/ * iwave_mix_devices ; 
 int* load_mixer_volumes (char*,int /*<<< orphan*/ ,int) ; 
 int nr_ad1848_devs ; 
 scalar_t__ soundpro ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 int /*<<< orphan*/ * spro_mix_devices ; 

__attribute__((used)) static void ad1848_mixer_reset(ad1848_info * devc)
{
	int i;
	char name[32];
	unsigned long flags;

	devc->mix_devices = &(ad1848_mix_devices[0]);

	sprintf(name, "%s_%d", devc->chip_name, nr_ad1848_devs);

	for (i = 0; i < 32; i++)
		devc->mixer_reroute[i] = i;

	devc->supported_rec_devices = MODE1_REC_DEVICES;

	switch (devc->model)
	{
		case MD_4231:
		case MD_4231A:
		case MD_1845:
		case MD_1845_SSCAPE:
			devc->supported_devices = MODE2_MIXER_DEVICES;
			break;

		case MD_C930:
			devc->supported_devices = C930_MIXER_DEVICES;
			devc->mix_devices = &(c930_mix_devices[0]);
			break;

		case MD_IWAVE:
			devc->supported_devices = MODE3_MIXER_DEVICES;
			devc->mix_devices = &(iwave_mix_devices[0]);
			break;

		case MD_42xB:
		case MD_4239:
			devc->mix_devices = &(cs42xb_mix_devices[0]);
			devc->supported_devices = MODE3_MIXER_DEVICES;
			break;
		case MD_4232:
		case MD_4235:
		case MD_4236:
			devc->supported_devices = MODE3_MIXER_DEVICES;
			break;

		case MD_1848:
			if (soundpro) {
				devc->supported_devices = SPRO_MIXER_DEVICES;
				devc->supported_rec_devices = SPRO_REC_DEVICES;
				devc->mix_devices = &(spro_mix_devices[0]);
				break;
			}

		default:
			devc->supported_devices = MODE1_MIXER_DEVICES;
	}

	devc->orig_devices = devc->supported_devices;
	devc->orig_rec_devices = devc->supported_rec_devices;

	devc->levels = load_mixer_volumes(name, default_mixer_levels, 1);

	for (i = 0; i < SOUND_MIXER_NRDEVICES; i++)
	{
		if (devc->supported_devices & (1 << i))
			ad1848_mixer_set(devc, i, devc->levels[i]);
	}
	
	ad1848_set_recmask(devc, SOUND_MASK_MIC);
	
	devc->mixer_output_port = devc->levels[31] | AUDIO_HEADPHONE | AUDIO_LINE_OUT;

	spin_lock_irqsave(&devc->lock,flags);
	if (!soundpro) {
		if (devc->mixer_output_port & AUDIO_SPEAKER)
			ad_write(devc, 26, ad_read(devc, 26) & ~0x40);	/* Unmute mono out */
		else
			ad_write(devc, 26, ad_read(devc, 26) | 0x40);	/* Mute mono out */
	} else {
		/*
		 * From the "wouldn't it be nice if the mixer API had (better)
		 * support for custom stuff" category
		 */
		/* Enable surround mode and SB16 mixer */
		ad_write(devc, 16, 0x60);
	}
	spin_unlock_irqrestore(&devc->lock,flags);
}