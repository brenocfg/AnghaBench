#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ intr_active; } ;
typedef  TYPE_1__ vmidi_devc ;
struct TYPE_4__ {TYPE_1__* devc; } ;

/* Variables and functions */
 int ENXIO ; 
 TYPE_2__** midi_devs ; 

__attribute__((used)) static int v_midi_end_read (int dev)
{
	vmidi_devc *devc = midi_devs[dev]->devc;
	if (devc == NULL)
		return -ENXIO;

	devc->intr_active = 0;
	return 0;
}