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
typedef  int uint32_t ;

/* Variables and functions */
 int F (int,int,int) ; 
 int G (int,int,int) ; 
 int H (int,int,int) ; 
 int I (int,int,int) ; 
 int K1 ; 
 int K2 ; 
 int K3 ; 
 int K4 ; 
 int ROTL (int,int) ; 
 int /*<<< orphan*/  br_range_dec32be (int*,int,unsigned char const*) ; 

void
br_sha1_round(const unsigned char *buf, uint32_t *val)
{
	uint32_t m[80];
	uint32_t a, b, c, d, e;
	int i;

	a = val[0];
	b = val[1];
	c = val[2];
	d = val[3];
	e = val[4];
	br_range_dec32be(m, 16, buf);
	for (i = 16; i < 80; i ++) {
		uint32_t x = m[i - 3] ^ m[i - 8] ^ m[i - 14] ^ m[i - 16];
		m[i] = ROTL(x, 1);
	}

	for (i = 0; i < 20; i += 5) {
		e += ROTL(a, 5) + F(b, c, d) + K1 + m[i + 0]; b = ROTL(b, 30);
		d += ROTL(e, 5) + F(a, b, c) + K1 + m[i + 1]; a = ROTL(a, 30);
		c += ROTL(d, 5) + F(e, a, b) + K1 + m[i + 2]; e = ROTL(e, 30);
		b += ROTL(c, 5) + F(d, e, a) + K1 + m[i + 3]; d = ROTL(d, 30);
		a += ROTL(b, 5) + F(c, d, e) + K1 + m[i + 4]; c = ROTL(c, 30);
	}
	for (i = 20; i < 40; i += 5) {
		e += ROTL(a, 5) + G(b, c, d) + K2 + m[i + 0]; b = ROTL(b, 30);
		d += ROTL(e, 5) + G(a, b, c) + K2 + m[i + 1]; a = ROTL(a, 30);
		c += ROTL(d, 5) + G(e, a, b) + K2 + m[i + 2]; e = ROTL(e, 30);
		b += ROTL(c, 5) + G(d, e, a) + K2 + m[i + 3]; d = ROTL(d, 30);
		a += ROTL(b, 5) + G(c, d, e) + K2 + m[i + 4]; c = ROTL(c, 30);
	}
	for (i = 40; i < 60; i += 5) {
		e += ROTL(a, 5) + H(b, c, d) + K3 + m[i + 0]; b = ROTL(b, 30);
		d += ROTL(e, 5) + H(a, b, c) + K3 + m[i + 1]; a = ROTL(a, 30);
		c += ROTL(d, 5) + H(e, a, b) + K3 + m[i + 2]; e = ROTL(e, 30);
		b += ROTL(c, 5) + H(d, e, a) + K3 + m[i + 3]; d = ROTL(d, 30);
		a += ROTL(b, 5) + H(c, d, e) + K3 + m[i + 4]; c = ROTL(c, 30);
	}
	for (i = 60; i < 80; i += 5) {
		e += ROTL(a, 5) + I(b, c, d) + K4 + m[i + 0]; b = ROTL(b, 30);
		d += ROTL(e, 5) + I(a, b, c) + K4 + m[i + 1]; a = ROTL(a, 30);
		c += ROTL(d, 5) + I(e, a, b) + K4 + m[i + 2]; e = ROTL(e, 30);
		b += ROTL(c, 5) + I(d, e, a) + K4 + m[i + 3]; d = ROTL(d, 30);
		a += ROTL(b, 5) + I(c, d, e) + K4 + m[i + 4]; c = ROTL(c, 30);
	}

	val[0] += a;
	val[1] += b;
	val[2] += c;
	val[3] += d;
	val[4] += e;
}