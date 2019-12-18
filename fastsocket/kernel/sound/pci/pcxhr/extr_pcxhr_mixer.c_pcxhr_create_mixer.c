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
struct snd_pcxhr {int num_cards; scalar_t__ nb_streams_play; scalar_t__ nb_streams_capt; int /*<<< orphan*/  card; scalar_t__ is_hr_stereo; struct snd_pcxhr** chip; int /*<<< orphan*/  mixer_mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  p; } ;
struct snd_kcontrol_new {char* name; int private_value; int count; TYPE_1__ tlv; } ;
struct pcxhr_mgr {int num_cards; scalar_t__ nb_streams_play; scalar_t__ nb_streams_capt; int /*<<< orphan*/  card; scalar_t__ is_hr_stereo; struct pcxhr_mgr** chip; int /*<<< orphan*/  mixer_mutex; } ;

/* Variables and functions */
 int PCXHR_PLAYBACK_STREAMS ; 
 int /*<<< orphan*/  db_scale_a_hr222_capture ; 
 int /*<<< orphan*/  db_scale_a_hr222_playback ; 
 int /*<<< orphan*/  db_scale_analog_capture ; 
 int /*<<< orphan*/  db_scale_analog_playback ; 
 int hr222_add_mic_controls (struct snd_pcxhr*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct snd_kcontrol_new pcxhr_control_analog_level ; 
 struct snd_kcontrol_new pcxhr_control_audio_src ; 
 struct snd_kcontrol_new pcxhr_control_capture_iec958 ; 
 struct snd_kcontrol_new pcxhr_control_capture_iec958_mask ; 
 struct snd_kcontrol_new pcxhr_control_clock_rate ; 
 struct snd_kcontrol_new pcxhr_control_clock_type ; 
 struct snd_kcontrol_new pcxhr_control_monitor_sw ; 
 struct snd_kcontrol_new pcxhr_control_monitor_vol ; 
 struct snd_kcontrol_new pcxhr_control_output_switch ; 
 struct snd_kcontrol_new pcxhr_control_pcm_switch ; 
 struct snd_kcontrol_new pcxhr_control_playback_iec958 ; 
 struct snd_kcontrol_new pcxhr_control_playback_iec958_mask ; 
 int /*<<< orphan*/  pcxhr_init_audio_levels (struct snd_pcxhr*) ; 
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (struct snd_kcontrol_new*,struct snd_pcxhr*) ; 
 struct snd_kcontrol_new snd_pcxhr_pcm_vol ; 

int pcxhr_create_mixer(struct pcxhr_mgr *mgr)
{
	struct snd_pcxhr *chip;
	int err, i;

	mutex_init(&mgr->mixer_mutex); /* can be in another place */

	for (i = 0; i < mgr->num_cards; i++) {
		struct snd_kcontrol_new temp;
		chip = mgr->chip[i];

		if (chip->nb_streams_play) {
			/* analog output level control */
			temp = pcxhr_control_analog_level;
			temp.name = "Master Playback Volume";
			temp.private_value = 0; /* playback */
			if (mgr->is_hr_stereo)
				temp.tlv.p = db_scale_a_hr222_playback;
			else
				temp.tlv.p = db_scale_analog_playback;
			err = snd_ctl_add(chip->card,
					  snd_ctl_new1(&temp, chip));
			if (err < 0)
				return err;

			/* output mute controls */
			err = snd_ctl_add(chip->card,
				snd_ctl_new1(&pcxhr_control_output_switch,
					     chip));
			if (err < 0)
				return err;

			temp = snd_pcxhr_pcm_vol;
			temp.name = "PCM Playback Volume";
			temp.count = PCXHR_PLAYBACK_STREAMS;
			temp.private_value = 0; /* playback */
			err = snd_ctl_add(chip->card,
					  snd_ctl_new1(&temp, chip));
			if (err < 0)
				return err;

			err = snd_ctl_add(chip->card,
				snd_ctl_new1(&pcxhr_control_pcm_switch, chip));
			if (err < 0)
				return err;

			/* IEC958 controls */
			err = snd_ctl_add(chip->card,
				snd_ctl_new1(&pcxhr_control_playback_iec958_mask,
					     chip));
			if (err < 0)
				return err;

			err = snd_ctl_add(chip->card,
				snd_ctl_new1(&pcxhr_control_playback_iec958,
					     chip));
			if (err < 0)
				return err;
		}
		if (chip->nb_streams_capt) {
			/* analog input level control */
			temp = pcxhr_control_analog_level;
			temp.name = "Line Capture Volume";
			temp.private_value = 1; /* capture */
			if (mgr->is_hr_stereo)
				temp.tlv.p = db_scale_a_hr222_capture;
			else
				temp.tlv.p = db_scale_analog_capture;

			err = snd_ctl_add(chip->card,
					  snd_ctl_new1(&temp, chip));
			if (err < 0)
				return err;

			temp = snd_pcxhr_pcm_vol;
			temp.name = "PCM Capture Volume";
			temp.count = 1;
			temp.private_value = 1; /* capture */

			err = snd_ctl_add(chip->card,
					  snd_ctl_new1(&temp, chip));
			if (err < 0)
				return err;

			/* Audio source */
			err = snd_ctl_add(chip->card,
				snd_ctl_new1(&pcxhr_control_audio_src, chip));
			if (err < 0)
				return err;

			/* IEC958 controls */
			err = snd_ctl_add(chip->card,
				snd_ctl_new1(&pcxhr_control_capture_iec958_mask,
					     chip));
			if (err < 0)
				return err;

			err = snd_ctl_add(chip->card,
				snd_ctl_new1(&pcxhr_control_capture_iec958,
					     chip));
			if (err < 0)
				return err;

			if (mgr->is_hr_stereo) {
				err = hr222_add_mic_controls(chip);
				if (err < 0)
					return err;
			}
		}
		/* monitoring only if playback and capture device available */
		if (chip->nb_streams_capt > 0 && chip->nb_streams_play > 0) {
			/* monitoring */
			err = snd_ctl_add(chip->card,
				snd_ctl_new1(&pcxhr_control_monitor_vol, chip));
			if (err < 0)
				return err;

			err = snd_ctl_add(chip->card,
				snd_ctl_new1(&pcxhr_control_monitor_sw, chip));
			if (err < 0)
				return err;
		}

		if (i == 0) {
			/* clock mode only one control per pcxhr */
			err = snd_ctl_add(chip->card,
				snd_ctl_new1(&pcxhr_control_clock_type, mgr));
			if (err < 0)
				return err;
			/* non standard control used to scan
			 * the external clock presence/frequencies
			 */
			err = snd_ctl_add(chip->card,
				snd_ctl_new1(&pcxhr_control_clock_rate, mgr));
			if (err < 0)
				return err;
		}

		/* init values for the mixer data */
		pcxhr_init_audio_levels(chip);
	}

	return 0;
}