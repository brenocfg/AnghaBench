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
struct sha512 {int len; int* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  processblock (struct sha512*,int*) ; 

__attribute__((used)) static void pad(struct sha512 *s)
{
	unsigned r = s->len % 128;

	s->buf[r++] = 0x80;
	if (r > 112) {
		memset(s->buf + r, 0, 128 - r);
		r = 0;
		processblock(s, s->buf);
	}
	memset(s->buf + r, 0, 120 - r);
	s->len *= 8;
	s->buf[120] = s->len >> 56;
	s->buf[121] = s->len >> 48;
	s->buf[122] = s->len >> 40;
	s->buf[123] = s->len >> 32;
	s->buf[124] = s->len >> 24;
	s->buf[125] = s->len >> 16;
	s->buf[126] = s->len >> 8;
	s->buf[127] = s->len;
	processblock(s, s->buf);
}