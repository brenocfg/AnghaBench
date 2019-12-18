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
struct esschan {scalar_t__ mode; int fmt; int /*<<< orphan*/ * apu_mode; int /*<<< orphan*/ * apu; int /*<<< orphan*/ * base; } ;
struct es1968 {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 scalar_t__ ESM_MODE_CAPTURE ; 
 int ESS_FMT_STEREO ; 
 int /*<<< orphan*/  __apu_set_register (struct es1968*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_es1968_trigger_apu (struct es1968*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_es1968_pcm_start(struct es1968 *chip, struct esschan *es)
{
	spin_lock(&chip->reg_lock);
	__apu_set_register(chip, es->apu[0], 5, es->base[0]);
	snd_es1968_trigger_apu(chip, es->apu[0], es->apu_mode[0]);
	if (es->mode == ESM_MODE_CAPTURE) {
		__apu_set_register(chip, es->apu[2], 5, es->base[2]);
		snd_es1968_trigger_apu(chip, es->apu[2], es->apu_mode[2]);
	}
	if (es->fmt & ESS_FMT_STEREO) {
		__apu_set_register(chip, es->apu[1], 5, es->base[1]);
		snd_es1968_trigger_apu(chip, es->apu[1], es->apu_mode[1]);
		if (es->mode == ESM_MODE_CAPTURE) {
			__apu_set_register(chip, es->apu[3], 5, es->base[3]);
			snd_es1968_trigger_apu(chip, es->apu[3], es->apu_mode[3]);
		}
	}
	spin_unlock(&chip->reg_lock);
}