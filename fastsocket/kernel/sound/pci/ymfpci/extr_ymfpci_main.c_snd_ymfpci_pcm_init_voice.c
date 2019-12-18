#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct snd_ymfpci_voice {scalar_t__ number; struct snd_ymfpci_playback_bank* bank; } ;
struct snd_ymfpci_playback_bank {int left_gain; int left_gain_end; int right_gain; int right_gain_end; int eff2_gain; int eff2_gain_end; int eff3_gain; int eff3_gain_end; void* eg_gain_end; void* eg_gain; void* lpfK_end; void* lpfK; void* delta_end; void* delta; void* lpfQ; void* loop_end; void* base; void* format; } ;
struct snd_ymfpci_pcm {int use_441_slot; int buffer_size; int /*<<< orphan*/  swap_rear; scalar_t__ output_rear; scalar_t__ output_front; TYPE_3__* chip; TYPE_2__* substream; struct snd_ymfpci_voice** voices; } ;
struct snd_pcm_runtime {int rate; int channels; int dma_addr; int /*<<< orphan*/  format; } ;
struct TYPE_6__ {scalar_t__ device_id; int src441_used; int /*<<< orphan*/  voice_lock; TYPE_1__* pcm_mixer; } ;
struct TYPE_5__ {size_t number; } ;
struct TYPE_4__ {int left; int right; } ;

/* Variables and functions */
 scalar_t__ PCI_DEVICE_ID_YAMAHA_754 ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memset (struct snd_ymfpci_playback_bank*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 int snd_ymfpci_calc_delta (int) ; 
 int snd_ymfpci_calc_lpfK (int) ; 
 int snd_ymfpci_calc_lpfQ (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_ymfpci_pcm_init_voice(struct snd_ymfpci_pcm *ypcm, unsigned int voiceidx,
				      struct snd_pcm_runtime *runtime,
				      int has_pcm_volume)
{
	struct snd_ymfpci_voice *voice = ypcm->voices[voiceidx];
	u32 format;
	u32 delta = snd_ymfpci_calc_delta(runtime->rate);
	u32 lpfQ = snd_ymfpci_calc_lpfQ(runtime->rate);
	u32 lpfK = snd_ymfpci_calc_lpfK(runtime->rate);
	struct snd_ymfpci_playback_bank *bank;
	unsigned int nbank;
	u32 vol_left, vol_right;
	u8 use_left, use_right;
	unsigned long flags;

	if (snd_BUG_ON(!voice))
		return;
	if (runtime->channels == 1) {
		use_left = 1;
		use_right = 1;
	} else {
		use_left = (voiceidx & 1) == 0;
		use_right = !use_left;
	}
	if (has_pcm_volume) {
		vol_left = cpu_to_le32(ypcm->chip->pcm_mixer
				       [ypcm->substream->number].left << 15);
		vol_right = cpu_to_le32(ypcm->chip->pcm_mixer
					[ypcm->substream->number].right << 15);
	} else {
		vol_left = cpu_to_le32(0x40000000);
		vol_right = cpu_to_le32(0x40000000);
	}
	spin_lock_irqsave(&ypcm->chip->voice_lock, flags);
	format = runtime->channels == 2 ? 0x00010000 : 0;
	if (snd_pcm_format_width(runtime->format) == 8)
		format |= 0x80000000;
	else if (ypcm->chip->device_id == PCI_DEVICE_ID_YAMAHA_754 &&
		 runtime->rate == 44100 && runtime->channels == 2 &&
		 voiceidx == 0 && (ypcm->chip->src441_used == -1 ||
				   ypcm->chip->src441_used == voice->number)) {
		ypcm->chip->src441_used = voice->number;
		ypcm->use_441_slot = 1;
		format |= 0x10000000;
	}
	if (ypcm->chip->src441_used == voice->number &&
	    (format & 0x10000000) == 0) {
		ypcm->chip->src441_used = -1;
		ypcm->use_441_slot = 0;
	}
	if (runtime->channels == 2 && (voiceidx & 1) != 0)
		format |= 1;
	spin_unlock_irqrestore(&ypcm->chip->voice_lock, flags);
	for (nbank = 0; nbank < 2; nbank++) {
		bank = &voice->bank[nbank];
		memset(bank, 0, sizeof(*bank));
		bank->format = cpu_to_le32(format);
		bank->base = cpu_to_le32(runtime->dma_addr);
		bank->loop_end = cpu_to_le32(ypcm->buffer_size);
		bank->lpfQ = cpu_to_le32(lpfQ);
		bank->delta =
		bank->delta_end = cpu_to_le32(delta);
		bank->lpfK =
		bank->lpfK_end = cpu_to_le32(lpfK);
		bank->eg_gain =
		bank->eg_gain_end = cpu_to_le32(0x40000000);

		if (ypcm->output_front) {
			if (use_left) {
				bank->left_gain =
				bank->left_gain_end = vol_left;
			}
			if (use_right) {
				bank->right_gain =
				bank->right_gain_end = vol_right;
			}
		}
		if (ypcm->output_rear) {
		        if (!ypcm->swap_rear) {
        			if (use_left) {
        				bank->eff2_gain =
        				bank->eff2_gain_end = vol_left;
        			}
        			if (use_right) {
        				bank->eff3_gain =
        				bank->eff3_gain_end = vol_right;
        			}
		        } else {
        			/* The SPDIF out channels seem to be swapped, so we have
        			 * to swap them here, too.  The rear analog out channels
        			 * will be wrong, but otherwise AC3 would not work.
        			 */
        			if (use_left) {
        				bank->eff3_gain =
        				bank->eff3_gain_end = vol_left;
        			}
        			if (use_right) {
        				bank->eff2_gain =
        				bank->eff2_gain_end = vol_right;
        			}
        		}
                }
	}
}