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
struct snd_emu10k1 {int /*<<< orphan*/ * ac97; } ;
struct snd_ac97 {struct snd_emu10k1* private_data; } ;

/* Variables and functions */

__attribute__((used)) static void snd_emu10k1_mixer_free_ac97(struct snd_ac97 *ac97)
{
	struct snd_emu10k1 *emu = ac97->private_data;
	emu->ac97 = NULL;
}