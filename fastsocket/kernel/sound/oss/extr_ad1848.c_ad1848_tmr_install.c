#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int dev; } ;

/* Variables and functions */
 TYPE_1__ ad1848_tmr ; 
 TYPE_2__** audio_devs ; 
 int /*<<< orphan*/  sound_timer_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int timer_installed ; 

__attribute__((used)) static int ad1848_tmr_install(int dev)
{
	if (timer_installed != -1)
		return 0;	/* Don't install another timer */

	timer_installed = ad1848_tmr.dev = dev;
	sound_timer_init(&ad1848_tmr, audio_devs[dev]->name);

	return 1;
}