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
struct snd_ps3_card_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS3_AUDIO_AX_IS ; 
 int /*<<< orphan*/  PS3_AUDIO_CONFIG ; 
 int /*<<< orphan*/  PS3_AUDIO_CONFIG_CLEAR ; 
 int /*<<< orphan*/  PS3_AUDIO_INTR_0 ; 
 int snd_ps3_verify_dma_stop (struct snd_ps3_card_info*,int,int) ; 
 int /*<<< orphan*/  update_mask_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void snd_ps3_wait_for_dma_stop(struct snd_ps3_card_info *card)
{
	int stop_forced;
	/*
	 * wait for the last dma is done
	 */

	/*
	 * expected maximum DMA done time is 5.7ms + something (DMA itself).
	 * 5.7ms is from 16bit/sample 2ch 44.1Khz; the time next
	 * DMA kick event would occur.
	 */
	stop_forced = snd_ps3_verify_dma_stop(card, 700, 1);

	/*
	 * clear outstanding interrupts.
	 */
	update_reg(PS3_AUDIO_INTR_0, 0);
	update_reg(PS3_AUDIO_AX_IS, 0);

	/*
	 *revert CLEAR bit since it will not reset automatically after DMA stop
	 */
	if (stop_forced)
		update_mask_reg(PS3_AUDIO_CONFIG, ~PS3_AUDIO_CONFIG_CLEAR, 0);
	/* ensure the hardware sees changes */
	wmb();
}