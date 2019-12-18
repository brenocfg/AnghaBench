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
 int* isdn_audio_alaw_to_s16 ; 
 int /*<<< orphan*/  isdn_audio_put_bits (int,int,TYPE_1__*,unsigned char**,int*) ; 
 int* isdn_audio_ulaw_to_s16 ; 

int
isdn_audio_xlaw2adpcm(adpcm_state * s, int fmt, unsigned char *in,
		      unsigned char *out, int len)
{
	int a = s->a;
	int d = s->d;
	int nbits = s->nbits;
	int olen = 0;

	while (len--) {
		int e = 0,
		 nmax = 1 << (nbits - 1);
		int sign,
		 delta;

		if (fmt)
			delta = (isdn_audio_alaw_to_s16[*in++] >> 2) - a;
		else
			delta = (isdn_audio_ulaw_to_s16[*in++] >> 2) - a;
		if (delta < 0) {
			e = nmax;
			delta = -delta;
		}
		while (--nmax && delta > d) {
			delta -= d;
			e++;
		}
		if (nbits == 4 && ((e & 0x0f) == 0))
			e = 8;
		isdn_audio_put_bits(e, nbits, s, &out, &olen);
		sign = (e >> (nbits - 1)) ? -1 : 1;
		e &= bitmask[nbits - 1];

		a += sign * ((e << 1) + 1) * d >> 1;
		if (d & 1)
			a++;
		d = (d * Mx[nbits - 2][e] + 0x2000) >> 14;
		if (d < 5)
			d = 5;
	}
	s->a = a;
	s->d = d;
	return olen;
}