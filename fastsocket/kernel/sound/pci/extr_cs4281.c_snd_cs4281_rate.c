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

__attribute__((used)) static unsigned int snd_cs4281_rate(unsigned int rate, unsigned int *real_rate)
{
	unsigned int val = ~0;
	
	if (real_rate)
		*real_rate = rate;
	/* special "hardcoded" rates */
	switch (rate) {
	case 8000:	return 5;
	case 11025:	return 4;
	case 16000:	return 3;
	case 22050:	return 2;
	case 44100:	return 1;
	case 48000:	return 0;
	default:
		goto __variable;
	}
      __variable:
	val = 1536000 / rate;
	if (real_rate)
		*real_rate = 1536000 / val;
	return val;
}