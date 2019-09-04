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
typedef  int /*<<< orphan*/  uint8_t ;
struct sha512 {int len; int /*<<< orphan*/  const* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned long) ; 
 int /*<<< orphan*/  processblock (struct sha512*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void sha512_update(struct sha512 *s, const void *m, unsigned long len)
{
	const uint8_t *p = m;
	unsigned r = s->len % 128;

	s->len += len;
	if (r) {
		if (len < 128 - r) {
			memcpy(s->buf + r, p, len);
			return;
		}
		memcpy(s->buf + r, p, 128 - r);
		len -= 128 - r;
		p += 128 - r;
		processblock(s, s->buf);
	}
	for (; len >= 128; len -= 128, p += 128)
		processblock(s, p);
	memcpy(s->buf, p, len);
}