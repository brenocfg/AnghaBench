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
struct TYPE_2__ {int timer_enabled; } ;
struct snd_gus_card {TYPE_1__ gf1; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_GF1_GB_SOUND_BLASTER_CONTROL ; 
 int /*<<< orphan*/  snd_gf1_i_write8 (struct snd_gus_card*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void snd_gf1_default_interrupt_handler_timer2(struct snd_gus_card * gus)
{
	snd_gf1_i_write8(gus, SNDRV_GF1_GB_SOUND_BLASTER_CONTROL, gus->gf1.timer_enabled &= ~8);
}