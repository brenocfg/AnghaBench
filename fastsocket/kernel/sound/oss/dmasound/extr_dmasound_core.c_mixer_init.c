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
struct TYPE_4__ {int /*<<< orphan*/  (* mixer_init ) () ;} ;
struct TYPE_6__ {TYPE_1__ mach; scalar_t__ bass; scalar_t__ treble; } ;
struct TYPE_5__ {scalar_t__ busy; } ;

/* Variables and functions */
 TYPE_3__ dmasound ; 
 TYPE_2__ mixer ; 
 int /*<<< orphan*/  mixer_fops ; 
 int register_sound_mixer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void mixer_init(void)
{
#ifndef MODULE
	int mixer_unit;
#endif
	mixer_unit = register_sound_mixer(&mixer_fops, -1);
	if (mixer_unit < 0)
		return;

	mixer.busy = 0;
	dmasound.treble = 0;
	dmasound.bass = 0;
	if (dmasound.mach.mixer_init)
	    dmasound.mach.mixer_init();
}