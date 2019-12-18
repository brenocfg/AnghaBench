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
struct snd_ad1816a {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD1816A_INDIR_ADDR ; 
 int /*<<< orphan*/  AD1816A_INDIR_DATA_HIGH ; 
 int /*<<< orphan*/  AD1816A_INDIR_DATA_LOW ; 
 int /*<<< orphan*/  snd_ad1816a_out (struct snd_ad1816a*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void snd_ad1816a_write(struct snd_ad1816a *chip, unsigned char reg,
			      unsigned short value)
{
	snd_ad1816a_out(chip, AD1816A_INDIR_ADDR, reg & 0x3f);
	snd_ad1816a_out(chip, AD1816A_INDIR_DATA_LOW, value & 0xff);
	snd_ad1816a_out(chip, AD1816A_INDIR_DATA_HIGH, (value >> 8) & 0xff);
}