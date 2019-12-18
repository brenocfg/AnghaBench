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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ F (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ G (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ H (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ I (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__* K ; 
 size_t* MP ; 
 scalar_t__ ROTL (scalar_t__,int) ; 
 int /*<<< orphan*/  br_range_dec32le (scalar_t__*,int,unsigned char const*) ; 

void
br_md5_round(const unsigned char *buf, uint32_t *val)
{
	uint32_t m[16];
	uint32_t a, b, c, d;
	int i;

	a = val[0];
	b = val[1];
	c = val[2];
	d = val[3];
	/* obsolete
	for (i = 0; i < 16; i ++) {
		m[i] = br_dec32le(buf + (i << 2));
	}
	*/
	br_range_dec32le(m, 16, buf);

	for (i = 0; i < 16; i += 4) {
		a = b + ROTL(a + F(b, c, d) + m[i + 0] + K[i + 0],  7);
		d = a + ROTL(d + F(a, b, c) + m[i + 1] + K[i + 1], 12);
		c = d + ROTL(c + F(d, a, b) + m[i + 2] + K[i + 2], 17);
		b = c + ROTL(b + F(c, d, a) + m[i + 3] + K[i + 3], 22);
	}
	for (i = 16; i < 32; i += 4) {
		a = b + ROTL(a + G(b, c, d) + m[MP[i - 16]] + K[i + 0],  5);
		d = a + ROTL(d + G(a, b, c) + m[MP[i - 15]] + K[i + 1],  9);
		c = d + ROTL(c + G(d, a, b) + m[MP[i - 14]] + K[i + 2], 14);
		b = c + ROTL(b + G(c, d, a) + m[MP[i - 13]] + K[i + 3], 20);
	}
	for (i = 32; i < 48; i += 4) {
		a = b + ROTL(a + H(b, c, d) + m[MP[i - 16]] + K[i + 0],  4);
		d = a + ROTL(d + H(a, b, c) + m[MP[i - 15]] + K[i + 1], 11);
		c = d + ROTL(c + H(d, a, b) + m[MP[i - 14]] + K[i + 2], 16);
		b = c + ROTL(b + H(c, d, a) + m[MP[i - 13]] + K[i + 3], 23);
	}
	for (i = 48; i < 64; i += 4) {
		a = b + ROTL(a + I(b, c, d) + m[MP[i - 16]] + K[i + 0],  6);
		d = a + ROTL(d + I(a, b, c) + m[MP[i - 15]] + K[i + 1], 10);
		c = d + ROTL(c + I(d, a, b) + m[MP[i - 14]] + K[i + 2], 15);
		b = c + ROTL(b + I(c, d, a) + m[MP[i - 13]] + K[i + 3], 21);
	}

	val[0] += a;
	val[1] += b;
	val[2] += c;
	val[3] += d;
}