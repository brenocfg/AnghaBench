#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ busy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_DEV_STATUS ; 
 int register_sound_special (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ state ; 
 int /*<<< orphan*/  state_fops ; 

__attribute__((used)) static int state_init(void)
{
#ifndef MODULE
	int state_unit;
#endif
	state_unit = register_sound_special(&state_fops, SND_DEV_STATUS);
	if (state_unit < 0)
		return state_unit ;
	state.busy = 0;
	return 0 ;
}