#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int irq_mode; int trigger_bits; int /*<<< orphan*/  trg_intrflag; int /*<<< orphan*/  trg_bytes; int /*<<< orphan*/  trg_buf; } ;
typedef  TYPE_1__ sb_devc ;
struct TYPE_5__ {TYPE_1__* devc; } ;

/* Variables and functions */
#define  IMODE_INPUT 129 
#define  IMODE_OUTPUT 128 
 TYPE_3__** audio_devs ; 
 int /*<<< orphan*/  sb20_audio_output_block (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb20_audio_start_input (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_dsp_command (TYPE_1__*,int) ; 

__attribute__((used)) static void sb20_audio_trigger(int dev, int bits)
{
	sb_devc *devc = audio_devs[dev]->devc;
	bits &= devc->irq_mode;

	if (!bits)
		sb_dsp_command(devc, 0xd0);	/* Halt DMA */
	else
	{
		switch (devc->irq_mode)
		{
			case IMODE_INPUT:
				sb20_audio_start_input(dev, devc->trg_buf, devc->trg_bytes,
						devc->trg_intrflag);
				break;

			case IMODE_OUTPUT:
				sb20_audio_output_block(dev, devc->trg_buf, devc->trg_bytes,
						devc->trg_intrflag);
			    break;
		}
	}
	devc->trigger_bits = bits;
}