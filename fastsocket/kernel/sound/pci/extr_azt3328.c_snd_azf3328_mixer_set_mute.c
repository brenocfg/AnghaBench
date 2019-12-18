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
struct snd_azf3328 {unsigned int mixer_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  AZF_MUTE_BIT ; 
 int snd_azf3328_io_reg_setb (unsigned long,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
snd_azf3328_mixer_set_mute(const struct snd_azf3328 *chip,
			   unsigned reg, bool do_mute
)
{
	unsigned long portbase = chip->mixer_io + reg + 1;
	bool updated;

	/* the mute bit is on the *second* (i.e. right) register of a
	 * left/right channel setting */
	updated = snd_azf3328_io_reg_setb(portbase, AZF_MUTE_BIT, do_mute);

	/* indicate whether it was muted before */
	return (do_mute) ? !updated : updated;
}