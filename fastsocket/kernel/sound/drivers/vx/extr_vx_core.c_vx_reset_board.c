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
struct vx_core {int freq; int /*<<< orphan*/  uer_bits; TYPE_1__* ops; int /*<<< orphan*/  uer_detected; int /*<<< orphan*/  clock_mode; int /*<<< orphan*/  clock_source; int /*<<< orphan*/  audio_source; int /*<<< orphan*/  audio_source_target; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset_board ) (struct vx_core*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  INTERNAL_QUARTZ ; 
 int /*<<< orphan*/  SNDRV_PCM_DEFAULT_CON_SPDIF ; 
 int /*<<< orphan*/  VX_AUDIO_SRC_LINE ; 
 int /*<<< orphan*/  VX_CLOCK_MODE_AUTO ; 
 int /*<<< orphan*/  VX_UER_MODE_NOT_PRESENT ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  stub1 (struct vx_core*,int) ; 
 scalar_t__ vx_is_pcmcia (struct vx_core*) ; 
 int /*<<< orphan*/  vx_reset_codec (struct vx_core*,int) ; 
 int /*<<< orphan*/  vx_reset_dsp (struct vx_core*) ; 
 int /*<<< orphan*/  vx_set_iec958_status (struct vx_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vx_set_internal_clock (struct vx_core*,int) ; 
 int /*<<< orphan*/  vx_test_and_ack (struct vx_core*) ; 
 int /*<<< orphan*/  vx_validate_irq (struct vx_core*,int) ; 

__attribute__((used)) static void vx_reset_board(struct vx_core *chip, int cold_reset)
{
	if (snd_BUG_ON(!chip->ops->reset_board))
		return;

	/* current source, later sync'ed with target */
	chip->audio_source = VX_AUDIO_SRC_LINE;
	if (cold_reset) {
		chip->audio_source_target = chip->audio_source;
		chip->clock_source = INTERNAL_QUARTZ;
		chip->clock_mode = VX_CLOCK_MODE_AUTO;
		chip->freq = 48000;
		chip->uer_detected = VX_UER_MODE_NOT_PRESENT;
		chip->uer_bits = SNDRV_PCM_DEFAULT_CON_SPDIF;
	}

	chip->ops->reset_board(chip, cold_reset);

	vx_reset_codec(chip, cold_reset);

	vx_set_internal_clock(chip, chip->freq);

	/* Reset the DSP */
	vx_reset_dsp(chip);

	if (vx_is_pcmcia(chip)) {
		/* Acknowledge any pending IRQ and reset the MEMIRQ flag. */
		vx_test_and_ack(chip);
		vx_validate_irq(chip, 1);
	}

	/* init CBits */
	vx_set_iec958_status(chip, chip->uer_bits);
}