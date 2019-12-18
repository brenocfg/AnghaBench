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
struct snd_pcm_runtime {int channels; unsigned int dma_addr; int buffer_size; unsigned int period_size; int rate; int /*<<< orphan*/  format; } ;
struct cmipci_pcm {int fmt; int shift; unsigned int offset; int dma_size; int ch; scalar_t__ running; scalar_t__ is_dac; } ;
struct cmipci {unsigned int ctrl; int /*<<< orphan*/  reg_lock; scalar_t__ chip_version; scalar_t__ can_96k; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_ADC48K44K ; 
 unsigned int CM_ASFC_MASK ; 
 unsigned int CM_ASFC_SHIFT ; 
 unsigned int CM_CH0FMT_MASK ; 
 unsigned int CM_CH0FMT_SHIFT ; 
 unsigned int CM_CH0_SRATE_128K ; 
 unsigned int CM_CH0_SRATE_88K ; 
 unsigned int CM_CH0_SRATE_96K ; 
 int CM_CH0_SRATE_MASK ; 
 unsigned int CM_CH1FMT_MASK ; 
 unsigned int CM_CH1FMT_SHIFT ; 
 unsigned int CM_CHADC0 ; 
 unsigned int CM_CHADC1 ; 
 unsigned int CM_DSFC_MASK ; 
 unsigned int CM_DSFC_SHIFT ; 
 unsigned int CM_REG_CH0_FRAME1 ; 
 unsigned int CM_REG_CH0_FRAME2 ; 
 unsigned int CM_REG_CH1_FRAME1 ; 
 unsigned int CM_REG_CH1_FRAME2 ; 
 unsigned int CM_REG_CHFORMAT ; 
 int /*<<< orphan*/  CM_REG_EXT_MISC ; 
 unsigned int CM_REG_FUNCTRL0 ; 
 unsigned int CM_REG_FUNCTRL1 ; 
 int EINVAL ; 
 scalar_t__ set_dac_channels (struct cmipci*,struct cmipci_pcm*,int) ; 
 int /*<<< orphan*/  snd_BUG () ; 
 int /*<<< orphan*/  snd_cmipci_clear_bit (struct cmipci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int snd_cmipci_rate_freq (int) ; 
 unsigned int snd_cmipci_read (struct cmipci*,unsigned int) ; 
 int /*<<< orphan*/  snd_cmipci_set_bit (struct cmipci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cmipci_write (struct cmipci*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  snd_cmipci_write_w (struct cmipci*,unsigned int,unsigned int) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_printd (char*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_cmipci_pcm_prepare(struct cmipci *cm, struct cmipci_pcm *rec,
				 struct snd_pcm_substream *substream)
{
	unsigned int reg, freq, freq_ext, val;
	unsigned int period_size;
	struct snd_pcm_runtime *runtime = substream->runtime;

	rec->fmt = 0;
	rec->shift = 0;
	if (snd_pcm_format_width(runtime->format) >= 16) {
		rec->fmt |= 0x02;
		if (snd_pcm_format_width(runtime->format) > 16)
			rec->shift++; /* 24/32bit */
	}
	if (runtime->channels > 1)
		rec->fmt |= 0x01;
	if (rec->is_dac && set_dac_channels(cm, rec, runtime->channels) < 0) {
		snd_printd("cannot set dac channels\n");
		return -EINVAL;
	}

	rec->offset = runtime->dma_addr;
	/* buffer and period sizes in frame */
	rec->dma_size = runtime->buffer_size << rec->shift;
	period_size = runtime->period_size << rec->shift;
	if (runtime->channels > 2) {
		/* multi-channels */
		rec->dma_size = (rec->dma_size * runtime->channels) / 2;
		period_size = (period_size * runtime->channels) / 2;
	}

	spin_lock_irq(&cm->reg_lock);

	/* set buffer address */
	reg = rec->ch ? CM_REG_CH1_FRAME1 : CM_REG_CH0_FRAME1;
	snd_cmipci_write(cm, reg, rec->offset);
	/* program sample counts */
	reg = rec->ch ? CM_REG_CH1_FRAME2 : CM_REG_CH0_FRAME2;
	snd_cmipci_write_w(cm, reg, rec->dma_size - 1);
	snd_cmipci_write_w(cm, reg + 2, period_size - 1);

	/* set adc/dac flag */
	val = rec->ch ? CM_CHADC1 : CM_CHADC0;
	if (rec->is_dac)
		cm->ctrl &= ~val;
	else
		cm->ctrl |= val;
	snd_cmipci_write(cm, CM_REG_FUNCTRL0, cm->ctrl);
	//snd_printd("cmipci: functrl0 = %08x\n", cm->ctrl);

	/* set sample rate */
	freq = 0;
	freq_ext = 0;
	if (runtime->rate > 48000)
		switch (runtime->rate) {
		case 88200:  freq_ext = CM_CH0_SRATE_88K; break;
		case 96000:  freq_ext = CM_CH0_SRATE_96K; break;
		case 128000: freq_ext = CM_CH0_SRATE_128K; break;
		default:     snd_BUG(); break;
		}
	else
		freq = snd_cmipci_rate_freq(runtime->rate);
	val = snd_cmipci_read(cm, CM_REG_FUNCTRL1);
	if (rec->ch) {
		val &= ~CM_DSFC_MASK;
		val |= (freq << CM_DSFC_SHIFT) & CM_DSFC_MASK;
	} else {
		val &= ~CM_ASFC_MASK;
		val |= (freq << CM_ASFC_SHIFT) & CM_ASFC_MASK;
	}
	snd_cmipci_write(cm, CM_REG_FUNCTRL1, val);
	//snd_printd("cmipci: functrl1 = %08x\n", val);

	/* set format */
	val = snd_cmipci_read(cm, CM_REG_CHFORMAT);
	if (rec->ch) {
		val &= ~CM_CH1FMT_MASK;
		val |= rec->fmt << CM_CH1FMT_SHIFT;
	} else {
		val &= ~CM_CH0FMT_MASK;
		val |= rec->fmt << CM_CH0FMT_SHIFT;
	}
	if (cm->can_96k) {
		val &= ~(CM_CH0_SRATE_MASK << (rec->ch * 2));
		val |= freq_ext << (rec->ch * 2);
	}
	snd_cmipci_write(cm, CM_REG_CHFORMAT, val);
	//snd_printd("cmipci: chformat = %08x\n", val);

	if (!rec->is_dac && cm->chip_version) {
		if (runtime->rate > 44100)
			snd_cmipci_set_bit(cm, CM_REG_EXT_MISC, CM_ADC48K44K);
		else
			snd_cmipci_clear_bit(cm, CM_REG_EXT_MISC, CM_ADC48K44K);
	}

	rec->running = 0;
	spin_unlock_irq(&cm->reg_lock);

	return 0;
}