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
struct snd_ac97 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_AD_JACK_SPDIF ; 
 int /*<<< orphan*/  ad1981_jacks_whitelist ; 
 scalar_t__ check_list (struct snd_ac97*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_update_bits (struct snd_ac97*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void check_ad1981_hp_jack_sense(struct snd_ac97 *ac97)
{
	if (check_list(ac97, ad1981_jacks_whitelist))
		/* enable headphone jack sense */
		snd_ac97_update_bits(ac97, AC97_AD_JACK_SPDIF, 1<<11, 1<<11);
}