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
struct sha512 {int* h; } ;

/* Variables and functions */
 int /*<<< orphan*/  pad (struct sha512*) ; 

__attribute__((used)) static void sha512_sum(struct sha512 *s, uint8_t *md)
{
	int i;

	pad(s);
	for (i = 0; i < 8; i++) {
		md[8*i] = s->h[i] >> 56;
		md[8*i+1] = s->h[i] >> 48;
		md[8*i+2] = s->h[i] >> 40;
		md[8*i+3] = s->h[i] >> 32;
		md[8*i+4] = s->h[i] >> 24;
		md[8*i+5] = s->h[i] >> 16;
		md[8*i+6] = s->h[i] >> 8;
		md[8*i+7] = s->h[i];
	}
}