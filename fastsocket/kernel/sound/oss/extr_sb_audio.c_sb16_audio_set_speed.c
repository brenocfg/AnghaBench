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
struct TYPE_3__ {scalar_t__ submodel; int speed; } ;
typedef  TYPE_1__ sb_devc ;
struct TYPE_4__ {TYPE_1__* devc; } ;

/* Variables and functions */
 scalar_t__ SUBMDL_ALS100 ; 
 TYPE_2__** audio_devs ; 

__attribute__((used)) static int sb16_audio_set_speed(int dev, int speed)
{
	sb_devc *devc = audio_devs[dev]->devc;
	int	max_speed = devc->submodel == SUBMDL_ALS100 ? 48000 : 44100;

	if (speed > 0)
	{
		if (speed < 5000)
			speed = 5000;

		if (speed > max_speed)
			speed = max_speed;

		devc->speed = speed;
	}
	return devc->speed;
}