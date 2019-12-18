#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int my_mixerdev; } ;
typedef  TYPE_1__ sb_devc ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mixer_devs ; 
 int /*<<< orphan*/  sbmixnum ; 
 int /*<<< orphan*/  sound_unload_mixerdev (size_t) ; 

void sb_mixer_unload(sb_devc *devc)
{
	if (devc->my_mixerdev == -1)
		return;

	kfree(mixer_devs[devc->my_mixerdev]);
	sound_unload_mixerdev(devc->my_mixerdev);
	sbmixnum--;
}