#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_cs46xx {struct dsp_spos_instance* dsp_spos_instance; } ;
struct dsp_spos_instance {int spdif_status_out; TYPE_2__* asynch_tx_scb; TYPE_2__* spdif_pcm_input_scb; TYPE_1__* master_mix_scb; } ;
struct TYPE_4__ {TYPE_1__* parent_scb_ptr; } ;
struct TYPE_3__ {TYPE_2__* next_scb_ptr; } ;

/* Variables and functions */
 int DSP_SPDIF_STATUS_OUTPUT_ENABLED ; 
 int DSP_SPDIF_STATUS_PLAYBACK_OPEN ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  SPDIFO_IP_OUTPUT_BUFFER1 ; 
 int /*<<< orphan*/  _dsp_clear_sample_buffer (struct snd_cs46xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cs46xx_dsp_remove_scb (struct snd_cs46xx*,TYPE_2__*) ; 
 scalar_t__ snd_BUG_ON (int) ; 

int  cs46xx_dsp_disable_spdif_out (struct snd_cs46xx *chip)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;

	/* dont touch anything if SPDIF is open */
	if ( ins->spdif_status_out & DSP_SPDIF_STATUS_PLAYBACK_OPEN) {
		ins->spdif_status_out &= ~DSP_SPDIF_STATUS_OUTPUT_ENABLED;
		return -EBUSY;
	}

	/* check integrety */
	if (snd_BUG_ON(!ins->asynch_tx_scb))
		return -EINVAL;
	if (snd_BUG_ON(!ins->spdif_pcm_input_scb))
		return -EINVAL;
	if (snd_BUG_ON(ins->master_mix_scb->next_scb_ptr != ins->asynch_tx_scb))
		return -EINVAL;
	if (snd_BUG_ON(ins->asynch_tx_scb->parent_scb_ptr !=
		       ins->master_mix_scb))
		return -EINVAL;

	cs46xx_dsp_remove_scb (chip,ins->spdif_pcm_input_scb);
	cs46xx_dsp_remove_scb (chip,ins->asynch_tx_scb);

	ins->spdif_pcm_input_scb = NULL;
	ins->asynch_tx_scb = NULL;

	/* clear buffer to prevent any undesired noise */
	_dsp_clear_sample_buffer(chip,SPDIFO_IP_OUTPUT_BUFFER1,256);

	/* monitor state */
	ins->spdif_status_out  &= ~DSP_SPDIF_STATUS_OUTPUT_ENABLED;


	return 0;
}