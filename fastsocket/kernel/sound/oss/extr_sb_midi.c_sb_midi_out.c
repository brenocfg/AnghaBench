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
struct TYPE_4__ {int midi_broken; } ;
typedef  TYPE_1__ sb_devc ;
struct TYPE_5__ {TYPE_1__* devc; } ;

/* Variables and functions */
 TYPE_3__** midi_devs ; 
 int /*<<< orphan*/  sb_dsp_command (TYPE_1__*,unsigned char) ; 

__attribute__((used)) static int sb_midi_out(int dev, unsigned char midi_byte)
{
	sb_devc *devc = midi_devs[dev]->devc;

	if (devc == NULL)
		return 1;

	if (devc->midi_broken)
		return 1;

	if (!sb_dsp_command(devc, midi_byte))
	{
		devc->midi_broken = 1;
		return 1;
	}
	return 1;
}