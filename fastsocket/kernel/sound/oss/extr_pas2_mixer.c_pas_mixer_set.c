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

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 unsigned int POSSIBLE_RECORDING_DEVICES ; 
#define  SOUND_MIXER_ALTPCM 140 
#define  SOUND_MIXER_BASS 139 
#define  SOUND_MIXER_CD 138 
#define  SOUND_MIXER_IMIX 137 
#define  SOUND_MIXER_LINE 136 
#define  SOUND_MIXER_MIC 135 
 int SOUND_MIXER_NRDEVICES ; 
#define  SOUND_MIXER_PCM 134 
#define  SOUND_MIXER_RECLEV 133 
#define  SOUND_MIXER_RECSRC 132 
#define  SOUND_MIXER_SPEAKER 131 
#define  SOUND_MIXER_SYNTH 130 
#define  SOUND_MIXER_TREBLE 129 
#define  SOUND_MIXER_VOLUME 128 
 int* levels ; 
 int mixer_output (int,int,int,int,int) ; 
 int /*<<< orphan*/  printk (char*,int,unsigned int) ; 
 int rec_devices ; 

__attribute__((used)) static int
pas_mixer_set(int whichDev, unsigned int level)
{
	int             left, right, devmask, changed, i, mixer = 0;

	DEB(printk("static int pas_mixer_set(int whichDev = %d, unsigned int level = %X)\n", whichDev, level));

	left = level & 0x7f;
	right = (level & 0x7f00) >> 8;

	if (whichDev < SOUND_MIXER_NRDEVICES) {
		if ((1 << whichDev) & rec_devices)
			mixer = 0x20;
		else
			mixer = 0x00;
	}

	switch (whichDev)
	  {
	  case SOUND_MIXER_VOLUME:	/* Master volume (0-63) */
		  levels[whichDev] = mixer_output(right, left, 63, 0x01, 0);
		  break;

		  /*
		   * Note! Bass and Treble are mono devices. Will use just the left
		   * channel.
		   */
	  case SOUND_MIXER_BASS:	/* Bass (0-12) */
		  levels[whichDev] = mixer_output(right, left, 12, 0x03, 0);
		  break;
	  case SOUND_MIXER_TREBLE:	/* Treble (0-12) */
		  levels[whichDev] = mixer_output(right, left, 12, 0x04, 0);
		  break;

	  case SOUND_MIXER_SYNTH:	/* Internal synthesizer (0-31) */
		  levels[whichDev] = mixer_output(right, left, 31, 0x10 | 0x00, mixer);
		  break;
	  case SOUND_MIXER_PCM:	/* PAS PCM (0-31) */
		  levels[whichDev] = mixer_output(right, left, 31, 0x10 | 0x05, mixer);
		  break;
	  case SOUND_MIXER_ALTPCM:	/* SB PCM (0-31) */
		  levels[whichDev] = mixer_output(right, left, 31, 0x10 | 0x07, mixer);
		  break;
	  case SOUND_MIXER_SPEAKER:	/* PC speaker (0-31) */
		  levels[whichDev] = mixer_output(right, left, 31, 0x10 | 0x06, mixer);
		  break;
	  case SOUND_MIXER_LINE:	/* External line (0-31) */
		  levels[whichDev] = mixer_output(right, left, 31, 0x10 | 0x02, mixer);
		  break;
	  case SOUND_MIXER_CD:	/* CD (0-31) */
		  levels[whichDev] = mixer_output(right, left, 31, 0x10 | 0x03, mixer);
		  break;
	  case SOUND_MIXER_MIC:	/* External microphone (0-31) */
		  levels[whichDev] = mixer_output(right, left, 31, 0x10 | 0x04, mixer);
		  break;
	  case SOUND_MIXER_IMIX:	/* Recording monitor (0-31) (Output mixer only) */
		  levels[whichDev] = mixer_output(right, left, 31, 0x10 | 0x01,
						  0x00);
		  break;
	  case SOUND_MIXER_RECLEV:	/* Recording level (0-15) */
		  levels[whichDev] = mixer_output(right, left, 15, 0x02, 0);
		  break;


	  case SOUND_MIXER_RECSRC:
		  devmask = level & POSSIBLE_RECORDING_DEVICES;

		  changed = devmask ^ rec_devices;
		  rec_devices = devmask;

		  for (i = 0; i < SOUND_MIXER_NRDEVICES; i++)
			  if (changed & (1 << i))
			    {
				    pas_mixer_set(i, levels[i]);
			    }
		  return rec_devices;
		  break;

	  default:
		  return -EINVAL;
	  }

	return (levels[whichDev]);
}