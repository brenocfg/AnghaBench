#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int a; int d; int nbits; } ;
typedef  TYPE_1__ adpcm_state ;

/* Variables and functions */
 int** Mx ; 
 int* bitmask ; 
 int isdn_audio_get_bits (TYPE_1__*,unsigned char**,int*) ; 
 size_t isdn_audio_linear2ulaw (int) ; 
 int /*<<< orphan*/ * isdn_audio_ulaw_to_alaw ; 

int
isdn_audio_adpcm2xlaw(adpcm_state * s, int fmt, unsigned char *in,
		      unsigned char *out, int len)
{
	int a = s->a;
	int d = s->d;
	int nbits = s->nbits;
	int olen = 0;

	while (len) {
		int e = isdn_audio_get_bits(s, &in, &len);
		int sign;

		if (nbits == 4 && e == 0)
			d = 4;
		sign = (e >> (nbits - 1)) ? -1 : 1;
		e &= bitmask[nbits - 1];
		a += sign * ((e << 1) + 1) * d >> 1;
		if (d & 1)
			a++;
		if (fmt)
			*out++ = isdn_audio_ulaw_to_alaw[
					 isdn_audio_linear2ulaw(a << 2)];
		else
			*out++ = isdn_audio_linear2ulaw(a << 2);
		olen++;
		d = (d * Mx[nbits - 2][e] + 0x2000) >> 14;
		if (d < 5)
			d = 5;
	}
	s->a = a;
	s->d = d;
	return olen;
}