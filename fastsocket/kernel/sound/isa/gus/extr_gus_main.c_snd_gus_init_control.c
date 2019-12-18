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
struct snd_gus_card {int /*<<< orphan*/  card; int /*<<< orphan*/  ace_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_gus_card*) ; 
 int /*<<< orphan*/  snd_gus_joystick_control ; 

__attribute__((used)) static void snd_gus_init_control(struct snd_gus_card *gus)
{
	if (!gus->ace_flag)
		snd_ctl_add(gus->card, snd_ctl_new1(&snd_gus_joystick_control, gus));
}