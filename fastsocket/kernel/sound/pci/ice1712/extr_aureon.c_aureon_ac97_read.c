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
struct snd_ice1712 {struct aureon_spec* spec; } ;
struct aureon_spec {unsigned short* stac9744; } ;

/* Variables and functions */

__attribute__((used)) static unsigned short aureon_ac97_read(struct snd_ice1712 *ice, unsigned short reg)
{
	struct aureon_spec *spec = ice->spec;
	return spec->stac9744[(reg & 0x7F) >> 1];
}