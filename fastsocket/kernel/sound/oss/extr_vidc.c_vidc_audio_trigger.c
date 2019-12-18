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
struct audio_operations {int flags; } ;

/* Variables and functions */
 int DMA_ACTIVE ; 
 int DMA_CR_E ; 
 int /*<<< orphan*/  IOMD_SD0CR ; 
 int PCM_ENABLE_OUTPUT ; 
 struct audio_operations** audio_devs ; 
 int /*<<< orphan*/  dma_interrupt ; 
 int /*<<< orphan*/  iomd_writeb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  vidc_audio_dma_interrupt ; 
 int /*<<< orphan*/  vidc_sound_dma_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vidc_audio_trigger(int dev, int enable_bits)
{
	struct audio_operations *adev = audio_devs[dev];

	if (enable_bits & PCM_ENABLE_OUTPUT) {
		if (!(adev->flags & DMA_ACTIVE)) {
			unsigned long flags;

			local_irq_save(flags);

			/* prevent recusion */
			adev->flags |= DMA_ACTIVE;

			dma_interrupt = vidc_audio_dma_interrupt;
			vidc_sound_dma_irq(0, NULL);
			iomd_writeb(DMA_CR_E | 0x10, IOMD_SD0CR);

			local_irq_restore(flags);
		}
	}
}