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
struct TYPE_4__ {scalar_t__ intr_active; } ;
typedef  TYPE_1__ sb_devc ;
struct TYPE_5__ {TYPE_1__* devc; } ;

/* Variables and functions */
 int ENXIO ; 
 TYPE_3__** midi_devs ; 
 int /*<<< orphan*/  sb_dsp_reset (TYPE_1__*) ; 

__attribute__((used)) static int sb_midi_end_read(int dev)
{
	sb_devc *devc = midi_devs[dev]->devc;

	if (devc == NULL)
		return -ENXIO;

	sb_dsp_reset(devc);
	devc->intr_active = 0;
	return 0;
}