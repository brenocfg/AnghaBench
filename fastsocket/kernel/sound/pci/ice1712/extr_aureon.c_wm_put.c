#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_ice1712 {TYPE_1__* akm; } ;
struct TYPE_2__ {unsigned short* images; } ;

/* Variables and functions */
 int /*<<< orphan*/  wm_put_nocache (struct snd_ice1712*,int,unsigned short) ; 

__attribute__((used)) static void wm_put(struct snd_ice1712 *ice, int reg, unsigned short val)
{
	wm_put_nocache(ice, reg, val);
	reg <<= 1;
	ice->akm[0].images[reg] = val >> 8;
	ice->akm[0].images[reg + 1] = val;
}