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
 unsigned short snd_ac97_read (struct snd_ac97*,int) ; 
 int /*<<< orphan*/  snd_ac97_write (struct snd_ac97*,int,unsigned short) ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int,int) ; 

__attribute__((used)) static void snd_ac97_change_volume_params2(struct snd_ac97 * ac97, int reg, int shift, unsigned char *max)
{
	unsigned short val, val1;

	*max = 63;
	val = 0x8080 | (0x20 << shift);
	snd_ac97_write(ac97, reg, val);
	val1 = snd_ac97_read(ac97, reg);
	if (val != val1) {
		*max = 31;
	}
	/* reset volume to zero */
	snd_ac97_write_cache(ac97, reg, 0x8080);
}