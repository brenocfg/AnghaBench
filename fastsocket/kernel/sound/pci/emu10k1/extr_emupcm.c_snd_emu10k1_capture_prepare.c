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
struct snd_pcm_runtime {int channels; int /*<<< orphan*/  rate; int /*<<< orphan*/  dma_addr; struct snd_emu10k1_pcm* private_data; } ;
struct snd_emu10k1_pcm {int type; scalar_t__ capture_bufsize; int capture_bs_val; int /*<<< orphan*/  capture_cr_val; int /*<<< orphan*/  capture_ba_reg; int /*<<< orphan*/  capture_bs_reg; } ;
struct snd_emu10k1 {scalar_t__ audigy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADCCR ; 
 int /*<<< orphan*/  ADCCR_LCHANENABLE ; 
 int /*<<< orphan*/  ADCCR_RCHANENABLE ; 
 int /*<<< orphan*/  A_ADCCR_LCHANENABLE ; 
 int /*<<< orphan*/  A_ADCCR_RCHANENABLE ; 
 int /*<<< orphan*/  A_FXWC1 ; 
 int /*<<< orphan*/  A_FXWC2 ; 
#define  CAPTURE_AC97ADC 129 
#define  CAPTURE_EFX 128 
 int /*<<< orphan*/  FXWC ; 
 scalar_t__* capture_period_sizes ; 
 int /*<<< orphan*/  snd_BUG () ; 
 int /*<<< orphan*/  snd_emu10k1_audigy_capture_rate_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1_capture_rate_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1_ptr_write (struct snd_emu10k1*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 struct snd_emu10k1* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_emu10k1_capture_prepare(struct snd_pcm_substream *substream)
{
	struct snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_emu10k1_pcm *epcm = runtime->private_data;
	int idx;

	/* zeroing the buffer size will stop capture */
	snd_emu10k1_ptr_write(emu, epcm->capture_bs_reg, 0, 0);
	switch (epcm->type) {
	case CAPTURE_AC97ADC:
		snd_emu10k1_ptr_write(emu, ADCCR, 0, 0);
		break;
	case CAPTURE_EFX:
		if (emu->audigy) {
			snd_emu10k1_ptr_write(emu, A_FXWC1, 0, 0);
			snd_emu10k1_ptr_write(emu, A_FXWC2, 0, 0);
		} else
			snd_emu10k1_ptr_write(emu, FXWC, 0, 0);
		break;
	default:
		break;
	}	
	snd_emu10k1_ptr_write(emu, epcm->capture_ba_reg, 0, runtime->dma_addr);
	epcm->capture_bufsize = snd_pcm_lib_buffer_bytes(substream);
	epcm->capture_bs_val = 0;
	for (idx = 0; idx < 31; idx++) {
		if (capture_period_sizes[idx] == epcm->capture_bufsize) {
			epcm->capture_bs_val = idx + 1;
			break;
		}
	}
	if (epcm->capture_bs_val == 0) {
		snd_BUG();
		epcm->capture_bs_val++;
	}
	if (epcm->type == CAPTURE_AC97ADC) {
		epcm->capture_cr_val = emu->audigy ? A_ADCCR_LCHANENABLE : ADCCR_LCHANENABLE;
		if (runtime->channels > 1)
			epcm->capture_cr_val |= emu->audigy ? A_ADCCR_RCHANENABLE : ADCCR_RCHANENABLE;
		epcm->capture_cr_val |= emu->audigy ?
			snd_emu10k1_audigy_capture_rate_reg(runtime->rate) :
			snd_emu10k1_capture_rate_reg(runtime->rate);
	}
	return 0;
}