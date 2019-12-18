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

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int SOUND_MIXER_NRDEVICES ; 
 int /*<<< orphan*/ * levels ; 
 int /*<<< orphan*/  pas_mixer_set (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  set_mode (int) ; 

__attribute__((used)) static void
pas_mixer_reset(void)
{
	int             foo;

	DEB(printk("pas2_mixer.c: void pas_mixer_reset(void)\n"));

	for (foo = 0; foo < SOUND_MIXER_NRDEVICES; foo++)
		pas_mixer_set(foo, levels[foo]);

	set_mode(0x04 | 0x01);
}