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

/* Variables and functions */
 int /*<<< orphan*/  WM_DEV ; 
 int /*<<< orphan*/  snd_vt1724_write_i2c (struct snd_ice1712*,int /*<<< orphan*/ ,unsigned short,unsigned short) ; 

__attribute__((used)) static void wm_put_nocache(struct snd_ice1712 *ice, int reg, unsigned short val)
{
	unsigned short cval;
	cval = (reg << 9) | val;
	snd_vt1724_write_i2c(ice, WM_DEV, cval >> 8, cval & 0xff);
}