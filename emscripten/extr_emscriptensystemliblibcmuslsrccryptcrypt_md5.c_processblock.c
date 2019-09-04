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
typedef  int uint32_t ;
struct md5 {int* h; } ;

/* Variables and functions */
 int /*<<< orphan*/  FF (int,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GG (int,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HH (int,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  II (int,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tab ; 

__attribute__((used)) static void processblock(struct md5 *s, const uint8_t *buf)
{
	uint32_t i, W[16], a, b, c, d;

	for (i = 0; i < 16; i++) {
		W[i] = buf[4*i];
		W[i] |= (uint32_t)buf[4*i+1]<<8;
		W[i] |= (uint32_t)buf[4*i+2]<<16;
		W[i] |= (uint32_t)buf[4*i+3]<<24;
	}

	a = s->h[0];
	b = s->h[1];
	c = s->h[2];
	d = s->h[3];

	i = 0;
	while (i < 16) {
		FF(a,b,c,d, W[i],  7, tab[i]); i++;
		FF(d,a,b,c, W[i], 12, tab[i]); i++;
		FF(c,d,a,b, W[i], 17, tab[i]); i++;
		FF(b,c,d,a, W[i], 22, tab[i]); i++;
	}
	while (i < 32) {
		GG(a,b,c,d, W[(5*i+1)%16],  5, tab[i]); i++;
		GG(d,a,b,c, W[(5*i+1)%16],  9, tab[i]); i++;
		GG(c,d,a,b, W[(5*i+1)%16], 14, tab[i]); i++;
		GG(b,c,d,a, W[(5*i+1)%16], 20, tab[i]); i++;
	}
	while (i < 48) {
		HH(a,b,c,d, W[(3*i+5)%16],  4, tab[i]); i++;
		HH(d,a,b,c, W[(3*i+5)%16], 11, tab[i]); i++;
		HH(c,d,a,b, W[(3*i+5)%16], 16, tab[i]); i++;
		HH(b,c,d,a, W[(3*i+5)%16], 23, tab[i]); i++;
	}
	while (i < 64) {
		II(a,b,c,d, W[7*i%16],  6, tab[i]); i++;
		II(d,a,b,c, W[7*i%16], 10, tab[i]); i++;
		II(c,d,a,b, W[7*i%16], 15, tab[i]); i++;
		II(b,c,d,a, W[7*i%16], 21, tab[i]); i++;
	}

	s->h[0] += a;
	s->h[1] += b;
	s->h[2] += c;
	s->h[3] += d;
}