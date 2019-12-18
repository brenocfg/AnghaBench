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

/* Variables and functions */

__attribute__((used)) static inline short int ulaw2linear(unsigned char ulaw)
{
	short mu, e, f, y;
	static short etab[] = {0, 132, 396, 924, 1980, 4092, 8316, 16764};

	mu = 255 - ulaw;
	e = (mu & 0x70) / 16;
	f = mu & 0x0f;
	y = f * (1 << (e + 3));
	y += etab[e];
	if (mu & 0x80)
		y = -y;
	return y;
}