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
struct snd_cs46xx {int dummy; } ;
struct dsp_symbol_entry {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * data; scalar_t__ size; scalar_t__ offset; } ;
struct TYPE_3__ {int /*<<< orphan*/ * symbols; scalar_t__ highest_frag_index; scalar_t__ nsymbols; } ;
struct dsp_spos_instance {int spdif_in_sample_rate; int dac_volume_right; int dac_volume_left; int spdif_input_volume_right; int spdif_input_volume_left; unsigned int spdif_csuv_default; unsigned int spdif_csuv_stream; int /*<<< orphan*/ * modules; scalar_t__ nmodules; scalar_t__ ntask; scalar_t__ nscb; TYPE_2__ code; TYPE_1__ symbol_table; } ;
struct dsp_module_desc {int dummy; } ;

/* Variables and functions */
 int DSP_CODE_BYTE_SIZE ; 
 int DSP_MAX_MODULES ; 
 int DSP_MAX_SYMBOLS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SNDRV_PCM_DEFAULT_CON_SPDIF ; 
 scalar_t__ _wrap_all_bits (int) ; 
 int /*<<< orphan*/  cs46xx_dsp_spos_destroy (struct snd_cs46xx*) ; 
 int /*<<< orphan*/  kfree (struct dsp_spos_instance*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct dsp_spos_instance* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vmalloc (int) ; 

struct dsp_spos_instance *cs46xx_dsp_spos_create (struct snd_cs46xx * chip)
{
	struct dsp_spos_instance * ins = kzalloc(sizeof(struct dsp_spos_instance), GFP_KERNEL);

	if (ins == NULL) 
		return NULL;

	/* better to use vmalloc for this big table */
	ins->symbol_table.nsymbols = 0;
	ins->symbol_table.symbols = vmalloc(sizeof(struct dsp_symbol_entry) *
					    DSP_MAX_SYMBOLS);
	ins->symbol_table.highest_frag_index = 0;

	if (ins->symbol_table.symbols == NULL) {
		cs46xx_dsp_spos_destroy(chip);
		goto error;
	}

	ins->code.offset = 0;
	ins->code.size = 0;
	ins->code.data = kmalloc(DSP_CODE_BYTE_SIZE, GFP_KERNEL);

	if (ins->code.data == NULL) {
		cs46xx_dsp_spos_destroy(chip);
		goto error;
	}

	ins->nscb = 0;
	ins->ntask = 0;

	ins->nmodules = 0;
	ins->modules = kmalloc(sizeof(struct dsp_module_desc) * DSP_MAX_MODULES, GFP_KERNEL);

	if (ins->modules == NULL) {
		cs46xx_dsp_spos_destroy(chip);
		goto error;
	}

	/* default SPDIF input sample rate
	   to 48000 khz */
	ins->spdif_in_sample_rate = 48000;

	/* maximize volume */
	ins->dac_volume_right = 0x8000;
	ins->dac_volume_left = 0x8000;
	ins->spdif_input_volume_right = 0x8000;
	ins->spdif_input_volume_left = 0x8000;

	/* set left and right validity bits and
	   default channel status */
	ins->spdif_csuv_default = 
		ins->spdif_csuv_stream =  
	 /* byte 0 */  ((unsigned int)_wrap_all_bits(  (SNDRV_PCM_DEFAULT_CON_SPDIF        & 0xff)) << 24) |
	 /* byte 1 */  ((unsigned int)_wrap_all_bits( ((SNDRV_PCM_DEFAULT_CON_SPDIF >> 8) & 0xff)) << 16) |
	 /* byte 3 */   (unsigned int)_wrap_all_bits(  (SNDRV_PCM_DEFAULT_CON_SPDIF >> 24) & 0xff) |
	 /* left and right validity bits */ (1 << 13) | (1 << 12);

	return ins;

error:
	kfree(ins);
	return NULL;
}