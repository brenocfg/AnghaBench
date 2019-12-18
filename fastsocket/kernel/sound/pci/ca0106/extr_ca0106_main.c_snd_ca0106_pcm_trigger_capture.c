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
struct snd_pcm_runtime {struct snd_ca0106_pcm* private_data; } ;
struct snd_ca0106_pcm {int channel_id; int running; } ;
struct snd_ca0106 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BASIC_INTERRUPT ; 
 int EINVAL ; 
 int /*<<< orphan*/  EXTENDED_INT_MASK ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int snd_ca0106_ptr_read (struct snd_ca0106*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ca0106_ptr_write (struct snd_ca0106*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct snd_ca0106* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_ca0106_pcm_trigger_capture(struct snd_pcm_substream *substream,
				    int cmd)
{
	struct snd_ca0106 *emu = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_ca0106_pcm *epcm = runtime->private_data;
	int channel = epcm->channel_id;
	int result = 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		snd_ca0106_ptr_write(emu, EXTENDED_INT_MASK, 0, snd_ca0106_ptr_read(emu, EXTENDED_INT_MASK, 0) | (0x110000<<channel));
		snd_ca0106_ptr_write(emu, BASIC_INTERRUPT, 0, snd_ca0106_ptr_read(emu, BASIC_INTERRUPT, 0)|(0x100<<channel));
		epcm->running = 1;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		snd_ca0106_ptr_write(emu, BASIC_INTERRUPT, 0, snd_ca0106_ptr_read(emu, BASIC_INTERRUPT, 0) & ~(0x100<<channel));
		snd_ca0106_ptr_write(emu, EXTENDED_INT_MASK, 0, snd_ca0106_ptr_read(emu, EXTENDED_INT_MASK, 0) & ~(0x110000<<channel));
		epcm->running = 0;
		break;
	default:
		result = -EINVAL;
		break;
	}
	return result;
}