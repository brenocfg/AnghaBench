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
struct TYPE_3__ {size_t pair_mididev; scalar_t__ input_opened; int /*<<< orphan*/  my_mididev; int /*<<< orphan*/  (* midi_input_intr ) (int /*<<< orphan*/ ,unsigned char) ;} ;
typedef  TYPE_1__ vmidi_devc ;
struct TYPE_4__ {TYPE_1__* devc; } ;

/* Variables and functions */
 int ENXIO ; 
 int MIDIbuf_avail (int /*<<< orphan*/ ) ; 
 TYPE_2__** midi_devs ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int v_midi_out (int dev, unsigned char midi_byte)
{
	vmidi_devc *devc = midi_devs[dev]->devc;
	vmidi_devc *pdevc;

	if (devc == NULL)
		return -ENXIO;

	pdevc = midi_devs[devc->pair_mididev]->devc;
	if (pdevc->input_opened > 0){
		if (MIDIbuf_avail(pdevc->my_mididev) > 500)
			return 0;
		pdevc->midi_input_intr (pdevc->my_mididev, midi_byte);
	}
	return 1;
}