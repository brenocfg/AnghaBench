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
struct TYPE_4__ {int /*<<< orphan*/  (* close ) (int) ;int /*<<< orphan*/  (* outputc ) (int,int) ;} ;
struct TYPE_3__ {int midi_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  leave_sysex (int) ; 
 TYPE_2__** midi_devs ; 
 int /*<<< orphan*/  stub1 (int,int) ; 
 int /*<<< orphan*/  stub2 (int) ; 
 TYPE_1__** synth_devs ; 

void
midi_synth_close(int dev)
{
	int             orig_dev = synth_devs[dev]->midi_dev;

	leave_sysex(dev);

	/*
	 * Shut up the synths by sending just single active sensing message.
	 */
	midi_devs[orig_dev]->outputc(orig_dev, 0xfe);

	midi_devs[orig_dev]->close(orig_dev);
}