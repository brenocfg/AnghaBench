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
struct snd_akm4xxx {int dummy; } ;

/* Variables and functions */
 int AK_GET_CHIP (int /*<<< orphan*/ ) ; 
 scalar_t__ AK_GET_INVERT (int /*<<< orphan*/ ) ; 
 scalar_t__ AK_GET_IPGA (int /*<<< orphan*/ ) ; 
 unsigned int AK_GET_MASK (int /*<<< orphan*/ ) ; 
 scalar_t__ AK_GET_NEEDSMSB (int /*<<< orphan*/ ) ; 
 scalar_t__ AK_GET_VOL_CVT (int /*<<< orphan*/ ) ; 
 unsigned char snd_akm4xxx_get_vol (struct snd_akm4xxx*,int,int) ; 
 int /*<<< orphan*/  snd_akm4xxx_set_vol (struct snd_akm4xxx*,int,int,unsigned char) ; 
 int /*<<< orphan*/  snd_akm4xxx_write (struct snd_akm4xxx*,int,int,unsigned char) ; 
 struct snd_akm4xxx* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 unsigned char* vol_cvt_datt ; 

__attribute__((used)) static int put_ak_reg(struct snd_kcontrol *kcontrol, int addr,
		      unsigned char nval)
{
	struct snd_akm4xxx *ak = snd_kcontrol_chip(kcontrol);
	unsigned int mask = AK_GET_MASK(kcontrol->private_value);
	int chip = AK_GET_CHIP(kcontrol->private_value);

	if (snd_akm4xxx_get_vol(ak, chip, addr) == nval)
		return 0;

	snd_akm4xxx_set_vol(ak, chip, addr, nval);
	if (AK_GET_VOL_CVT(kcontrol->private_value) && nval < 128)
		nval = vol_cvt_datt[nval];
	if (AK_GET_IPGA(kcontrol->private_value) && nval >= 128)
		nval++; /* need to correct + 1 since both 127 and 128 are 0dB */
	if (AK_GET_INVERT(kcontrol->private_value))
		nval = mask - nval;
	if (AK_GET_NEEDSMSB(kcontrol->private_value))
		nval |= 0x80;
	/* printk(KERN_DEBUG "DEBUG - AK writing reg: chip %x addr %x,
	   nval %x\n", chip, addr, nval); */
	snd_akm4xxx_write(ak, chip, addr, nval);
	return 1;
}