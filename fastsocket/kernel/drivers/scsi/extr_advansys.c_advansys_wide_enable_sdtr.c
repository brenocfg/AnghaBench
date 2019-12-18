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
typedef  int /*<<< orphan*/  AdvPortAddr ;

/* Variables and functions */
 int /*<<< orphan*/  ASC_MC_SDTR_ABLE ; 
 int /*<<< orphan*/  ASC_MC_SDTR_DONE ; 
 int /*<<< orphan*/  AdvReadWordLram (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  AdvWriteWordLram (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void
advansys_wide_enable_sdtr(AdvPortAddr iop_base, unsigned short tidmask)
{
	unsigned short cfg_word;
	AdvReadWordLram(iop_base, ASC_MC_SDTR_ABLE, cfg_word);
	if ((cfg_word & tidmask) != 0)
		return;

	cfg_word |= tidmask;
	AdvWriteWordLram(iop_base, ASC_MC_SDTR_ABLE, cfg_word);

	/*
	 * Clear the microcode "SDTR negotiation" done indicator for the
	 * target to cause it to negotiate with the new setting set above.
	 */
	AdvReadWordLram(iop_base, ASC_MC_SDTR_DONE, cfg_word);
	cfg_word &= ~tidmask;
	AdvWriteWordLram(iop_base, ASC_MC_SDTR_DONE, cfg_word);
}