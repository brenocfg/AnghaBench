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
struct snd_pcm_runtime {struct snd_ali_voice* private_data; } ;
struct snd_ali_voice {int /*<<< orphan*/  number; int /*<<< orphan*/  running; } ;
struct snd_ali {int /*<<< orphan*/  reg_lock; } ;
typedef  unsigned int snd_pcm_uframes_t ;

/* Variables and functions */
 scalar_t__ ALI_CSO_ALPHA_FMS ; 
 scalar_t__ ALI_GC_CIR ; 
 int /*<<< orphan*/  ALI_REG (struct snd_ali*,scalar_t__) ; 
 unsigned int inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_ali* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_ali_pointer(struct snd_pcm_substream *substream)
{
	struct snd_ali *codec = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_ali_voice *pvoice = runtime->private_data;
	unsigned int cso;

	spin_lock(&codec->reg_lock);
	if (!pvoice->running) {
		spin_unlock_irq(&codec->reg_lock);
		return 0;
	}
	outb(pvoice->number, ALI_REG(codec, ALI_GC_CIR));
	cso = inw(ALI_REG(codec, ALI_CSO_ALPHA_FMS + 2));
	spin_unlock(&codec->reg_lock);

	return cso;
}