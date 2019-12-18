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
struct TYPE_3__ {int channels; int tconst; int speed; } ;
typedef  TYPE_1__ sb_devc ;
struct TYPE_4__ {TYPE_1__* devc; } ;

/* Variables and functions */
 TYPE_2__** audio_devs ; 

__attribute__((used)) static int jazz16_audio_set_speed(int dev, int speed)
{
	sb_devc *devc = audio_devs[dev]->devc;

	if (speed > 0)
	{
		int tmp;
		int s = speed * devc->channels;

		if (speed < 5000)
			speed = 5000;
		if (speed > 44100)
			speed = 44100;

		devc->tconst = (256 - ((1000000 + s / 2) / s)) & 0xff;

		tmp = 256 - devc->tconst;
		speed = ((1000000 + tmp / 2) / tmp) / devc->channels;

		devc->speed = speed;
	}
	return devc->speed;
}