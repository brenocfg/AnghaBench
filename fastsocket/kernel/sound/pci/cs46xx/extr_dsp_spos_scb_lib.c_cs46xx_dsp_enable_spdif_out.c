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
struct dsp_spos_instance {int spdif_status_out; int asynch_tx_scb; scalar_t__ the_null_scb; int /*<<< orphan*/  spdif_pcm_input_scb; TYPE_1__* ref_snoop_scb; TYPE_2__* master_mix_scb; } ;
struct TYPE_4__ {scalar_t__ next_scb_ptr; } ;
struct TYPE_3__ {int address; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNCTX_SCB_ADDR ; 
 int DSP_SPDIF_STATUS_HW_ENABLED ; 
 int DSP_SPDIF_STATUS_OUTPUT_ENABLED ; 
 int DSP_SPDIF_STATUS_PLAYBACK_OPEN ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int OUTPUT_SNOOP_BUFFER ; 
 int /*<<< orphan*/  PCMSERIALINII_SCB_ADDR ; 
 int /*<<< orphan*/  SCB_ON_PARENT_NEXT_SCB ; 
 int /*<<< orphan*/  SCB_ON_PARENT_SUBLIST_SCB ; 
 int /*<<< orphan*/  SPDIFO_IP_OUTPUT_BUFFER1 ; 
 int /*<<< orphan*/  SPDIFO_SCB_INST ; 
 int cs46xx_dsp_create_asynch_fg_tx_scb (struct snd_cs46xx*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs46xx_dsp_create_pcm_serial_input_scb (struct snd_cs46xx*,char*,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs46xx_dsp_enable_spdif_hw (struct snd_cs46xx*) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_cs46xx_poke (struct snd_cs46xx*,int,int) ; 

int cs46xx_dsp_enable_spdif_out (struct snd_cs46xx *chip)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;

	if ( ! (ins->spdif_status_out & DSP_SPDIF_STATUS_HW_ENABLED) ) {
		cs46xx_dsp_enable_spdif_hw (chip);
	}

	/* dont touch anything if SPDIF is open */
	if ( ins->spdif_status_out & DSP_SPDIF_STATUS_PLAYBACK_OPEN) {
		/* when cs46xx_iec958_post_close(...) is called it
		   will call this function if necessary depending on
		   this bit */
		ins->spdif_status_out |= DSP_SPDIF_STATUS_OUTPUT_ENABLED;

		return -EBUSY;
	}

	if (snd_BUG_ON(ins->asynch_tx_scb))
		return -EINVAL;
	if (snd_BUG_ON(ins->master_mix_scb->next_scb_ptr !=
		       ins->the_null_scb))
		return -EINVAL;

	/* reset output snooper sample buffer pointer */
	snd_cs46xx_poke (chip, (ins->ref_snoop_scb->address + 2) << 2,
			 (OUTPUT_SNOOP_BUFFER + 0x10) << 0x10 );
	
	/* The asynch. transfer task */
	ins->asynch_tx_scb = cs46xx_dsp_create_asynch_fg_tx_scb(chip,"AsynchFGTxSCB",ASYNCTX_SCB_ADDR,
								SPDIFO_SCB_INST,
								SPDIFO_IP_OUTPUT_BUFFER1,
								ins->master_mix_scb,
								SCB_ON_PARENT_NEXT_SCB);
	if (!ins->asynch_tx_scb) return -ENOMEM;

	ins->spdif_pcm_input_scb = cs46xx_dsp_create_pcm_serial_input_scb(chip,"PCMSerialInput_II",
									  PCMSERIALINII_SCB_ADDR,
									  ins->ref_snoop_scb,
									  ins->asynch_tx_scb,
									  SCB_ON_PARENT_SUBLIST_SCB);
  
	
	if (!ins->spdif_pcm_input_scb) return -ENOMEM;

	/* monitor state */
	ins->spdif_status_out |= DSP_SPDIF_STATUS_OUTPUT_ENABLED;

	return 0;
}