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
struct snd_akm4xxx {int dummy; } ;

/* Variables and functions */
 unsigned char snd_akm4xxx_get (struct snd_akm4xxx*,int,int) ; 
 int /*<<< orphan*/  snd_akm4xxx_reset (struct snd_akm4xxx*,int) ; 
 int /*<<< orphan*/  snd_akm4xxx_write (struct snd_akm4xxx*,int,int,unsigned char) ; 

__attribute__((used)) static void vx442_ak4524_set_rate_val(struct snd_akm4xxx *ak, unsigned int rate)
{
	unsigned char val;

	val = (rate > 48000) ? 0x65 : 0x60;
	if (snd_akm4xxx_get(ak, 0, 0x02) != val ||
	    snd_akm4xxx_get(ak, 1, 0x02) != val) {
		snd_akm4xxx_reset(ak, 1);
		snd_akm4xxx_write(ak, 0, 0x02, val);
		snd_akm4xxx_write(ak, 1, 0x02, val);
		snd_akm4xxx_reset(ak, 0);
	}
}