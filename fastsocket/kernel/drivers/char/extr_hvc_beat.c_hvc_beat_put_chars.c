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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  beat_put_term_char (int /*<<< orphan*/ ,int,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  memcpy (unsigned long*,char const*,int) ; 

__attribute__((used)) static int hvc_beat_put_chars(uint32_t vtermno, const char *buf, int cnt)
{
	unsigned long kb[2];
	int rest, nlen;

	for (rest = cnt; rest > 0; rest -= nlen) {
		nlen = (rest > 16) ? 16 : rest;
		memcpy(kb, buf, nlen);
		beat_put_term_char(vtermno, nlen, kb[0], kb[1]);
		buf += nlen;
	}
	return cnt;
}