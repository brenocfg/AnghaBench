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
typedef  scalar_t__ u32 ;
struct snd_ac97 {struct nm256* private_data; } ;
struct nm256 {unsigned short* ac97_regs; scalar_t__ mixer_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int nm256_ac97_idx (unsigned short) ; 
 scalar_t__ snd_nm256_ac97_ready (struct nm256*) ; 
 int /*<<< orphan*/  snd_nm256_writew (struct nm256*,scalar_t__,unsigned short) ; 
 int /*<<< orphan*/  snd_printd (char*) ; 

__attribute__((used)) static void
snd_nm256_ac97_write(struct snd_ac97 *ac97,
		     unsigned short reg, unsigned short val)
{
	struct nm256 *chip = ac97->private_data;
	int tries = 2;
	int idx = nm256_ac97_idx(reg);
	u32 base;

	if (idx < 0)
		return;

	base = chip->mixer_base;

	snd_nm256_ac97_ready(chip);

	/* Wait for the write to take, too. */
	while (tries-- > 0) {
		snd_nm256_writew(chip, base + reg, val);
		msleep(1);  /* a little delay here seems better.. */
		if (snd_nm256_ac97_ready(chip)) {
			/* successful write: set cache */
			chip->ac97_regs[idx] = val;
			return;
		}
	}
	snd_printd("nm256: ac97 codec not ready..\n");
}