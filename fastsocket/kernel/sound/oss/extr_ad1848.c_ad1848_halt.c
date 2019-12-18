#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int open_mode; } ;
typedef  TYPE_1__ ad1848_port_info ;
struct TYPE_6__ {scalar_t__ audio_mode; } ;
typedef  TYPE_2__ ad1848_info ;
struct TYPE_7__ {scalar_t__ portc; scalar_t__ devc; } ;

/* Variables and functions */
 int OPEN_READ ; 
 int OPEN_WRITE ; 
 int /*<<< orphan*/  ad1848_halt_input (int) ; 
 int /*<<< orphan*/  ad1848_halt_output (int) ; 
 unsigned char ad_read (TYPE_2__*,int) ; 
 TYPE_3__** audio_devs ; 

__attribute__((used)) static void ad1848_halt(int dev)
{
	ad1848_info *devc = (ad1848_info *) audio_devs[dev]->devc;
	ad1848_port_info *portc = (ad1848_port_info *) audio_devs[dev]->portc;

	unsigned char   bits = ad_read(devc, 9);

	if (bits & 0x01 && (portc->open_mode & OPEN_WRITE))
		ad1848_halt_output(dev);

	if (bits & 0x02 && (portc->open_mode & OPEN_READ))
		ad1848_halt_input(dev);
	devc->audio_mode = 0;
}