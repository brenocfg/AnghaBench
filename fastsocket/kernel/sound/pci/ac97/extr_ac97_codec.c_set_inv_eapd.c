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
struct snd_kcontrol {int /*<<< orphan*/  private_value; } ;
struct snd_ac97 {int /*<<< orphan*/  scaps; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_POWERDOWN ; 
 int /*<<< orphan*/  AC97_SCAP_INV_EAPD ; 
 int /*<<< orphan*/  AC97_SINGLE_VALUE (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_update_bits (struct snd_ac97*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void set_inv_eapd(struct snd_ac97 *ac97, struct snd_kcontrol *kctl)
{
	kctl->private_value = AC97_SINGLE_VALUE(AC97_POWERDOWN, 15, 1, 0);
	snd_ac97_update_bits(ac97, AC97_POWERDOWN, (1<<15), (1<<15)); /* EAPD up */
	ac97->scaps |= AC97_SCAP_INV_EAPD;
}