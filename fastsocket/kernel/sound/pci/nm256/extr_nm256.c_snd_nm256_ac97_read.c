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
struct snd_ac97 {struct nm256* private_data; } ;
struct nm256 {unsigned short* ac97_regs; } ;

/* Variables and functions */
 int nm256_ac97_idx (unsigned short) ; 

__attribute__((used)) static unsigned short
snd_nm256_ac97_read(struct snd_ac97 *ac97, unsigned short reg)
{
	struct nm256 *chip = ac97->private_data;
	int idx = nm256_ac97_idx(reg);

	if (idx < 0)
		return 0;
	return chip->ac97_regs[idx];
}