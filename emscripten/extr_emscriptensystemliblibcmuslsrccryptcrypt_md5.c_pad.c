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
struct md5 {int len; int* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  processblock (struct md5*,int*) ; 

__attribute__((used)) static void pad(struct md5 *s)
{
	unsigned r = s->len % 64;

	s->buf[r++] = 0x80;
	if (r > 56) {
		memset(s->buf + r, 0, 64 - r);
		r = 0;
		processblock(s, s->buf);
	}
	memset(s->buf + r, 0, 56 - r);
	s->len *= 8;
	s->buf[56] = s->len;
	s->buf[57] = s->len >> 8;
	s->buf[58] = s->len >> 16;
	s->buf[59] = s->len >> 24;
	s->buf[60] = s->len >> 32;
	s->buf[61] = s->len >> 40;
	s->buf[62] = s->len >> 48;
	s->buf[63] = s->len >> 56;
	processblock(s, s->buf);
}