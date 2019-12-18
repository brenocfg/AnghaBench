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
struct snd_sb {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  snd_sbdsp_command (struct snd_sb*,unsigned char const) ; 

__attribute__((used)) static inline int command_seq(struct snd_sb *chip, const unsigned char *seq, int size)
{
	int i;
	for (i = 0; i < size; i++) {
		if (!snd_sbdsp_command(chip, seq[i]))
			return -EIO;
	}
	return 0;
}