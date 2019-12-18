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
 unsigned char MUX (int /*<<< orphan*/ ,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 

__attribute__((used)) static void
cond_rotate(uint32_t ctl, unsigned char *buf, size_t len, size_t num)
{
	unsigned char tmp[64];
	size_t u, v;

	for (u = 0, v = num; u < len; u ++) {
		tmp[u] = MUX(ctl, buf[v], buf[u]);
		if (++ v == len) {
			v = 0;
		}
	}
	memcpy(buf, tmp, len);
}