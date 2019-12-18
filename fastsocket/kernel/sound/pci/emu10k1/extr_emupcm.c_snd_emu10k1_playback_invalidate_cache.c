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
struct snd_pcm_runtime {int channels; int /*<<< orphan*/  format; } ;
struct snd_emu10k1_voice {unsigned int number; TYPE_2__* epcm; } ;
struct snd_emu10k1 {int dummy; } ;
struct TYPE_4__ {TYPE_1__* substream; } ;
struct TYPE_3__ {struct snd_pcm_runtime* runtime; } ;

/* Variables and functions */
 scalar_t__ CCR_CACHEINVALIDSIZE ; 
 scalar_t__ CCR_READADDRESS ; 
 scalar_t__ CD0 ; 
 unsigned int emu10k1_ccis (unsigned int,int) ; 
 int /*<<< orphan*/  snd_emu10k1_ptr_write (struct snd_emu10k1*,scalar_t__,unsigned int,unsigned int) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_emu10k1_playback_invalidate_cache(struct snd_emu10k1 *emu, int extra, struct snd_emu10k1_voice *evoice)
{
	struct snd_pcm_runtime *runtime;
	unsigned int voice, stereo, i, ccis, cra = 64, cs, sample;

	if (evoice == NULL)
		return;
	runtime = evoice->epcm->substream->runtime;
	voice = evoice->number;
	stereo = (!extra && runtime->channels == 2);
	sample = snd_pcm_format_width(runtime->format) == 16 ? 0 : 0x80808080;
	ccis = emu10k1_ccis(stereo, sample == 0);
	/* set cs to 2 * number of cache registers beside the invalidated */
	cs = (sample == 0) ? (32-ccis) : (64-ccis+1) >> 1;
	if (cs > 16) cs = 16;
	for (i = 0; i < cs; i++) {
		snd_emu10k1_ptr_write(emu, CD0 + i, voice, sample);
		if (stereo) {
			snd_emu10k1_ptr_write(emu, CD0 + i, voice + 1, sample);
		}
	}
	/* reset cache */
	snd_emu10k1_ptr_write(emu, CCR_CACHEINVALIDSIZE, voice, 0);
	snd_emu10k1_ptr_write(emu, CCR_READADDRESS, voice, cra);
	if (stereo) {
		snd_emu10k1_ptr_write(emu, CCR_CACHEINVALIDSIZE, voice + 1, 0);
		snd_emu10k1_ptr_write(emu, CCR_READADDRESS, voice + 1, cra);
	}
	/* fill cache */
	snd_emu10k1_ptr_write(emu, CCR_CACHEINVALIDSIZE, voice, ccis);
	if (stereo) {
		snd_emu10k1_ptr_write(emu, CCR_CACHEINVALIDSIZE, voice+1, ccis);
	}
}