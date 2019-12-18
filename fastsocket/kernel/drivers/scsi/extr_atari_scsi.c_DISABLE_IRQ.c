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

/* Variables and functions */
 int /*<<< orphan*/  IRQ_MFP_FSCSI ; 
 int /*<<< orphan*/  IRQ_TT_MFP_SCSI ; 
 scalar_t__ IS_A_TT () ; 
 int /*<<< orphan*/  atari_disable_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void DISABLE_IRQ(void)
{
	if (IS_A_TT())
		atari_disable_irq(IRQ_TT_MFP_SCSI);
	else
		atari_disable_irq(IRQ_MFP_FSCSI);
}