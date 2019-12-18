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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {unsigned int dma_addr; int period_size; int buffer_size; int /*<<< orphan*/  rate; struct snd_ali_voice* private_data; } ;
struct snd_ali_voice {scalar_t__ number; int count; int eso; struct snd_ali_voice* extra; } ;
struct snd_ali {int /*<<< orphan*/  reg_lock; scalar_t__ spdif_support; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALI_GLOBAL_CONTROL ; 
 scalar_t__ ALI_PCM_IN_CHANNEL ; 
 int /*<<< orphan*/  ALI_REG (struct snd_ali*,int /*<<< orphan*/ ) ; 
 scalar_t__ ALI_SPDIF_IN_CHANNEL ; 
 scalar_t__ ALI_SPDIF_OUT_CHANNEL ; 
 int ALI_SPDIF_OUT_CH_ENABLE ; 
 int inl (int /*<<< orphan*/ ) ; 
 unsigned int snd_ali_control_mode (struct snd_pcm_substream*) ; 
 unsigned int snd_ali_convert_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ali_disable_special_channel (struct snd_ali*,scalar_t__) ; 
 int /*<<< orphan*/  snd_ali_printk (char*,...) ; 
 int /*<<< orphan*/  snd_ali_set_spdif_out_rate (struct snd_ali*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ali_write_voice_regs (struct snd_ali*,scalar_t__,unsigned int,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned int,int,int,unsigned int,unsigned int) ; 
 struct snd_ali* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ali_playback_prepare(struct snd_pcm_substream *substream)
{
	struct snd_ali *codec = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_ali_voice *pvoice = runtime->private_data;
	struct snd_ali_voice *evoice = pvoice->extra;

	unsigned int LBA;
	unsigned int Delta;
	unsigned int ESO;
	unsigned int CTRL;
	unsigned int GVSEL;
	unsigned int PAN;
	unsigned int VOL;
	unsigned int EC;
	
	snd_ali_printk("playback_prepare ...\n");

	spin_lock_irq(&codec->reg_lock);	
	
	/* set Delta (rate) value */
	Delta = snd_ali_convert_rate(runtime->rate, 0);

	if (pvoice->number == ALI_SPDIF_IN_CHANNEL || 
	    pvoice->number == ALI_PCM_IN_CHANNEL)
		snd_ali_disable_special_channel(codec, pvoice->number);
	else if (codec->spdif_support &&
		 (inl(ALI_REG(codec, ALI_GLOBAL_CONTROL)) &
		  ALI_SPDIF_OUT_CH_ENABLE)
		 && pvoice->number == ALI_SPDIF_OUT_CHANNEL) {
		snd_ali_set_spdif_out_rate(codec, runtime->rate);
		Delta = 0x1000;
	}
	
	/* set Loop Back Address */
	LBA = runtime->dma_addr;

	/* set interrupt count size */
	pvoice->count = runtime->period_size;

	/* set target ESO for channel */
	pvoice->eso = runtime->buffer_size; 

	snd_ali_printk("playback_prepare: eso=%xh count=%xh\n",
		       pvoice->eso, pvoice->count);

	/* set ESO to capture first MIDLP interrupt */
	ESO = pvoice->eso -1;
	/* set ctrl mode */
	CTRL = snd_ali_control_mode(substream);

	GVSEL = 1;
	PAN = 0;
	VOL = 0;
	EC = 0;
	snd_ali_printk("playback_prepare:\n");
	snd_ali_printk("ch=%d, Rate=%d Delta=%xh,GVSEL=%xh,PAN=%xh,CTRL=%xh\n",
		       pvoice->number,runtime->rate,Delta,GVSEL,PAN,CTRL);
	snd_ali_write_voice_regs(codec,
				 pvoice->number,
				 LBA,
				 0,	/* cso */
				 ESO,
				 Delta,
				 0,	/* alpha */
				 GVSEL,
				 PAN,
				 VOL,
				 CTRL,
				 EC);
	if (evoice) {
		evoice->count = pvoice->count;
		evoice->eso = pvoice->count << 1;
		ESO = evoice->eso - 1;
		snd_ali_write_voice_regs(codec,
					 evoice->number,
					 LBA,
					 0,	/* cso */
					 ESO,
					 Delta,
					 0,	/* alpha */
					 GVSEL,
					 0x7f,
					 0x3ff,
					 CTRL,
					 EC);
	}
	spin_unlock_irq(&codec->reg_lock);
	return 0;
}