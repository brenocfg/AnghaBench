#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct address_info {size_t* slots; scalar_t__ io_base; } ;
struct TYPE_7__ {scalar_t__ base; int model; scalar_t__ pcibase; int caps; scalar_t__ dma8; scalar_t__ dma16; scalar_t__ irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  my_mididev; } ;
typedef  TYPE_1__ sb_devc ;
struct TYPE_8__ {TYPE_1__* devc; } ;

/* Variables and functions */
 int MDL_ESS ; 
 int SB_NO_AUDIO ; 
 int SB_NO_MIDI ; 
 TYPE_6__** audio_devs ; 
 TYPE_1__* detected_devc ; 
 int /*<<< orphan*/  free_irq (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 
 int /*<<< orphan*/  sb_mixer_unload (TYPE_1__*) ; 
 int /*<<< orphan*/  sound_free_dma (scalar_t__) ; 
 int /*<<< orphan*/  sound_unload_audiodev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sound_unload_mididev (int /*<<< orphan*/ ) ; 

void sb_dsp_unload(struct address_info *hw_config, int sbmpu)
{
	sb_devc *devc;

	devc = audio_devs[hw_config->slots[0]]->devc;

	if (devc && devc->base == hw_config->io_base)
	{
		if ((devc->model & MDL_ESS) && devc->pcibase)
			release_region(devc->pcibase, 8);

		release_region(devc->base, 16);

		if (!(devc->caps & SB_NO_AUDIO))
		{
			sound_free_dma(devc->dma8);
			if (devc->dma16 >= 0)
				sound_free_dma(devc->dma16);
		}
		if (!(devc->caps & SB_NO_AUDIO && devc->caps & SB_NO_MIDI))
		{
			if (devc->irq > 0)
				free_irq(devc->irq, devc);

			sb_mixer_unload(devc);
			/* We don't have to do this bit any more the UART401 is its own
				master  -- Krzysztof Halasa */
			/* But we have to do it, if UART401 is not detected */
			if (!sbmpu)
				sound_unload_mididev(devc->my_mididev);
			sound_unload_audiodev(devc->dev);
		}
		kfree(devc);
	}
	else
		release_region(hw_config->io_base, 16);

	kfree(detected_devc);
}