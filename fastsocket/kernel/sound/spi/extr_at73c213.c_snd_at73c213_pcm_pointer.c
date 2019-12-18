#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {scalar_t__ buffer_size; scalar_t__ dma_addr; } ;
struct snd_at73c213 {TYPE_1__* ssc; } ;
typedef  scalar_t__ snd_pcm_uframes_t ;
struct TYPE_2__ {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDC_TPR ; 
 scalar_t__ bytes_to_frames (struct snd_pcm_runtime*,unsigned long) ; 
 struct snd_at73c213* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 unsigned long ssc_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static snd_pcm_uframes_t
snd_at73c213_pcm_pointer(struct snd_pcm_substream *substream)
{
	struct snd_at73c213 *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	snd_pcm_uframes_t pos;
	unsigned long bytes;

	bytes = ssc_readl(chip->ssc->regs, PDC_TPR)
		- (unsigned long)runtime->dma_addr;

	pos = bytes_to_frames(runtime, bytes);
	if (pos >= runtime->buffer_size)
		pos -= runtime->buffer_size;

	return pos;
}