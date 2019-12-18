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
struct snd_ice1712 {int dummy; } ;
struct snd_ac97 {struct snd_ice1712* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_CMD ; 
 int /*<<< orphan*/  AC97_DATA ; 
 int /*<<< orphan*/  AC97_INDEX ; 
 unsigned char ICE1712_AC97_CAP_VSR ; 
 unsigned char ICE1712_AC97_PBK_VSR ; 
 unsigned char ICE1712_AC97_READ ; 
 unsigned char ICE1712_AC97_READY ; 
 unsigned char ICE1712_AC97_WRITE ; 
 int /*<<< orphan*/  ICEREG (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_ice1712_ac97_write(struct snd_ac97 *ac97,
				   unsigned short reg,
				   unsigned short val)
{
	struct snd_ice1712 *ice = ac97->private_data;
	int tm;
	unsigned char old_cmd = 0;

	for (tm = 0; tm < 0x10000; tm++) {
		old_cmd = inb(ICEREG(ice, AC97_CMD));
		if (old_cmd & (ICE1712_AC97_WRITE | ICE1712_AC97_READ))
			continue;
		if (!(old_cmd & ICE1712_AC97_READY))
			continue;
		break;
	}
	outb(reg, ICEREG(ice, AC97_INDEX));
	outw(val, ICEREG(ice, AC97_DATA));
	old_cmd &= ~(ICE1712_AC97_PBK_VSR | ICE1712_AC97_CAP_VSR);
	outb(old_cmd | ICE1712_AC97_WRITE, ICEREG(ice, AC97_CMD));
	for (tm = 0; tm < 0x10000; tm++)
		if ((inb(ICEREG(ice, AC97_CMD)) & ICE1712_AC97_WRITE) == 0)
			break;
}