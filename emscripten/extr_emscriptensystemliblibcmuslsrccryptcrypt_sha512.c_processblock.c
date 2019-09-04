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
typedef  int uint8_t ;
typedef  int uint64_t ;
struct sha512 {int* h; } ;

/* Variables and functions */
 int Ch (int,int,int) ; 
 int* K ; 
 int Maj (int,int,int) ; 
 int R0 (int) ; 
 int R1 (int) ; 
 int S0 (int) ; 
 int S1 (int) ; 

__attribute__((used)) static void processblock(struct sha512 *s, const uint8_t *buf)
{
	uint64_t W[80], t1, t2, a, b, c, d, e, f, g, h;
	int i;

	for (i = 0; i < 16; i++) {
		W[i] = (uint64_t)buf[8*i]<<56;
		W[i] |= (uint64_t)buf[8*i+1]<<48;
		W[i] |= (uint64_t)buf[8*i+2]<<40;
		W[i] |= (uint64_t)buf[8*i+3]<<32;
		W[i] |= (uint64_t)buf[8*i+4]<<24;
		W[i] |= (uint64_t)buf[8*i+5]<<16;
		W[i] |= (uint64_t)buf[8*i+6]<<8;
		W[i] |= buf[8*i+7];
	}
	for (; i < 80; i++)
		W[i] = R1(W[i-2]) + W[i-7] + R0(W[i-15]) + W[i-16];
	a = s->h[0];
	b = s->h[1];
	c = s->h[2];
	d = s->h[3];
	e = s->h[4];
	f = s->h[5];
	g = s->h[6];
	h = s->h[7];
	for (i = 0; i < 80; i++) {
		t1 = h + S1(e) + Ch(e,f,g) + K[i] + W[i];
		t2 = S0(a) + Maj(a,b,c);
		h = g;
		g = f;
		f = e;
		e = d + t1;
		d = c;
		c = b;
		b = a;
		a = t1 + t2;
	}
	s->h[0] += a;
	s->h[1] += b;
	s->h[2] += c;
	s->h[3] += d;
	s->h[4] += e;
	s->h[5] += f;
	s->h[6] += g;
	s->h[7] += h;
}