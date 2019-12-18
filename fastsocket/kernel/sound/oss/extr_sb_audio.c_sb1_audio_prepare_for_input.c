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
struct TYPE_4__ {int tconst; scalar_t__ trigger_bits; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ sb_devc ;
struct TYPE_5__ {TYPE_1__* devc; } ;

/* Variables and functions */
 int DSP_CMD_SPKOFF ; 
 TYPE_3__** audio_devs ; 
 scalar_t__ sb_dsp_command (TYPE_1__*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sb1_audio_prepare_for_input(int dev, int bsize, int bcount)
{
	sb_devc *devc = audio_devs[dev]->devc;
	unsigned long flags;

	spin_lock_irqsave(&devc->lock, flags);
	if (sb_dsp_command(devc, 0x40))
		sb_dsp_command(devc, devc->tconst);
	sb_dsp_command(devc, DSP_CMD_SPKOFF);
	spin_unlock_irqrestore(&devc->lock, flags);

	devc->trigger_bits = 0;
	return 0;
}