#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_tea575x {int /*<<< orphan*/ * vd; } ;

/* Variables and functions */
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

void snd_tea575x_exit(struct snd_tea575x *tea)
{
	if (tea->vd) {
		video_unregister_device(tea->vd);
		tea->vd = NULL;
	}
}