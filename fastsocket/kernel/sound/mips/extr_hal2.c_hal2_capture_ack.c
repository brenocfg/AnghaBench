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
struct snd_pcm_substream {int dummy; } ;
struct hal2_codec {int /*<<< orphan*/  pcm_indirect; } ;
struct snd_hal2 {struct hal2_codec adc; } ;

/* Variables and functions */
 int /*<<< orphan*/  hal2_capture_transfer ; 
 int /*<<< orphan*/  snd_pcm_indirect_capture_transfer (struct snd_pcm_substream*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct snd_hal2* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int hal2_capture_ack(struct snd_pcm_substream *substream)
{
	struct snd_hal2 *hal2 = snd_pcm_substream_chip(substream);
	struct hal2_codec *adc = &hal2->adc;

	snd_pcm_indirect_capture_transfer(substream,
					  &adc->pcm_indirect,
					  hal2_capture_transfer);
	return 0;
}