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
struct TYPE_3__ {int channels; int speed; } ;
typedef  TYPE_1__ sb_devc ;
struct TYPE_4__ {TYPE_1__* devc; } ;

/* Variables and functions */
 TYPE_2__** audio_devs ; 
 int /*<<< orphan*/  sb201_audio_set_speed (int,int) ; 

__attribute__((used)) static int sbpro_audio_set_speed(int dev, int speed)
{
	sb_devc *devc = audio_devs[dev]->devc;

	if (speed > 0)
	{
		if (speed < 4000)
			speed = 4000;
		if (speed > 44100)
			speed = 44100;
		if (devc->channels > 1 && speed > 22050)
			speed = 22050;
		sb201_audio_set_speed(dev, speed);
	}
	return devc->speed;
}