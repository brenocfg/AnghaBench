#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int open_mode; } ;
typedef  TYPE_1__ wavnc_port_info ;
struct TYPE_5__ {scalar_t__ audio_mode; } ;
typedef  TYPE_2__ wavnc_info ;
struct TYPE_6__ {scalar_t__ devc; scalar_t__ portc; } ;

/* Variables and functions */
 int OPEN_READ ; 
 int OPEN_WRITE ; 
 TYPE_3__** audio_devs ; 
 int /*<<< orphan*/  waveartist_halt_input (int) ; 
 int /*<<< orphan*/  waveartist_halt_output (int) ; 

__attribute__((used)) static void
waveartist_halt(int dev)
{
	wavnc_port_info	*portc = (wavnc_port_info *) audio_devs[dev]->portc;
	wavnc_info	*devc;

	if (portc->open_mode & OPEN_WRITE)
		waveartist_halt_output(dev);

	if (portc->open_mode & OPEN_READ)
		waveartist_halt_input(dev);

	devc = (wavnc_info *) audio_devs[dev]->devc;
	devc->audio_mode = 0;
}