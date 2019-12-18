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
struct snd_sb_csp {int running; int acc_format; int mode; int acc_channels; int acc_width; int acc_rates; TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSP_PROGRAM_ADPCM_CAPTURE ; 
 int /*<<< orphan*/  CSP_PROGRAM_ADPCM_INIT ; 
 int /*<<< orphan*/  CSP_PROGRAM_ADPCM_PLAYBACK ; 
 int /*<<< orphan*/  CSP_PROGRAM_ALAW ; 
 int /*<<< orphan*/  CSP_PROGRAM_MULAW ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENXIO ; 
 int SNDRV_PCM_FMTBIT_A_LAW ; 
 int SNDRV_PCM_FMTBIT_IMA_ADPCM ; 
 int SNDRV_PCM_FMTBIT_MU_LAW ; 
#define  SNDRV_PCM_FORMAT_A_LAW 130 
#define  SNDRV_PCM_FORMAT_IMA_ADPCM 129 
#define  SNDRV_PCM_FORMAT_MU_LAW 128 
 int /*<<< orphan*/  SNDRV_SB_CSP_LOAD_INITBLOCK ; 
 int SNDRV_SB_CSP_MODE_DSP_READ ; 
 int SNDRV_SB_CSP_MODE_DSP_WRITE ; 
 int SNDRV_SB_CSP_MONO ; 
 int SNDRV_SB_CSP_RATE_ALL ; 
 int SNDRV_SB_CSP_SAMPLE_16BIT ; 
 int SNDRV_SB_CSP_STEREO ; 
 int SNDRV_SB_CSP_ST_AUTO ; 
 int SNDRV_SB_CSP_ST_LOADED ; 
 int SNDRV_SB_CSP_ST_RUNNING ; 
 int /*<<< orphan*/  set_mode_register (TYPE_1__*,int) ; 
 int snd_sb_csp_firmware_load (struct snd_sb_csp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_sb_csp_autoload(struct snd_sb_csp * p, int pcm_sfmt, int play_rec_mode)
{
	unsigned long flags;
	int err = 0;

	/* if CSP is running or manually loaded then exit */
	if (p->running & (SNDRV_SB_CSP_ST_RUNNING | SNDRV_SB_CSP_ST_LOADED)) 
		return -EBUSY;

	/* autoload microcode only if requested hardware codec is not already loaded */
	if (((1 << pcm_sfmt) & p->acc_format) && (play_rec_mode & p->mode)) {
		p->running = SNDRV_SB_CSP_ST_AUTO;
	} else {
		switch (pcm_sfmt) {
		case SNDRV_PCM_FORMAT_MU_LAW:
			err = snd_sb_csp_firmware_load(p, CSP_PROGRAM_MULAW, 0);
			p->acc_format = SNDRV_PCM_FMTBIT_MU_LAW;
			p->mode = SNDRV_SB_CSP_MODE_DSP_READ | SNDRV_SB_CSP_MODE_DSP_WRITE;
			break;
		case SNDRV_PCM_FORMAT_A_LAW:
			err = snd_sb_csp_firmware_load(p, CSP_PROGRAM_ALAW, 0);
			p->acc_format = SNDRV_PCM_FMTBIT_A_LAW;
			p->mode = SNDRV_SB_CSP_MODE_DSP_READ | SNDRV_SB_CSP_MODE_DSP_WRITE;
			break;
		case SNDRV_PCM_FORMAT_IMA_ADPCM:
			err = snd_sb_csp_firmware_load(p, CSP_PROGRAM_ADPCM_INIT,
						       SNDRV_SB_CSP_LOAD_INITBLOCK);
			if (err)
				break;
			if (play_rec_mode == SNDRV_SB_CSP_MODE_DSP_WRITE) {
				err = snd_sb_csp_firmware_load
					(p, CSP_PROGRAM_ADPCM_PLAYBACK, 0);
				p->mode = SNDRV_SB_CSP_MODE_DSP_WRITE;
			} else {
				err = snd_sb_csp_firmware_load
					(p, CSP_PROGRAM_ADPCM_CAPTURE, 0);
				p->mode = SNDRV_SB_CSP_MODE_DSP_READ;
			}
			p->acc_format = SNDRV_PCM_FMTBIT_IMA_ADPCM;
			break;				  
		default:
			/* Decouple CSP from IRQ and DMAREQ lines */
			if (p->running & SNDRV_SB_CSP_ST_AUTO) {
				spin_lock_irqsave(&p->chip->reg_lock, flags);
				set_mode_register(p->chip, 0xfc);
				set_mode_register(p->chip, 0x00);
				spin_unlock_irqrestore(&p->chip->reg_lock, flags);
				p->running = 0;			/* clear autoloaded flag */
			}
			return -EINVAL;
		}
		if (err) {
			p->acc_format = 0;
			p->acc_channels = p->acc_width = p->acc_rates = 0;

			p->running = 0;				/* clear autoloaded flag */
			p->mode = 0;
			return (err);
		} else {
			p->running = SNDRV_SB_CSP_ST_AUTO;	/* set autoloaded flag */
			p->acc_width = SNDRV_SB_CSP_SAMPLE_16BIT;	/* only 16 bit data */
			p->acc_channels = SNDRV_SB_CSP_MONO | SNDRV_SB_CSP_STEREO;
			p->acc_rates = SNDRV_SB_CSP_RATE_ALL;	/* HW codecs accept all rates */
		}   

	}
	return (p->running & SNDRV_SB_CSP_ST_AUTO) ? 0 : -ENXIO;
}