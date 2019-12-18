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
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {int hw_queue_size; } ;
struct hal2_codec {TYPE_1__ pcm_indirect; } ;
struct snd_hal2 {struct hal2_codec dac; } ;

/* Variables and functions */
 int H2_BUF_SIZE ; 
 int /*<<< orphan*/  hal2_playback_transfer ; 
 int /*<<< orphan*/  snd_pcm_indirect_playback_transfer (struct snd_pcm_substream*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct snd_hal2* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int hal2_playback_ack(struct snd_pcm_substream *substream)
{
	struct snd_hal2 *hal2 = snd_pcm_substream_chip(substream);
	struct hal2_codec *dac = &hal2->dac;

	dac->pcm_indirect.hw_queue_size = H2_BUF_SIZE / 2;
	snd_pcm_indirect_playback_transfer(substream,
					   &dac->pcm_indirect,
					   hal2_playback_transfer);
	return 0;
}