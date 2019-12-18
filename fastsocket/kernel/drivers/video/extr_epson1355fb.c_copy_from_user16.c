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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY_READ ; 
 scalar_t__ __get_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  access_ok (int /*<<< orphan*/ ,void const*,unsigned long) ; 
 int /*<<< orphan*/  fb_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_writew (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned long copy_from_user16(void *to, const void *from,
					     unsigned long n)
{
	u16 *dst = (u16 *) to;
	u16 *src = (u16 *) from;

	if (!access_ok(VERIFY_READ, from, n))
		return n;

	while (n > 1) {
		u16 v;
		if (__get_user(v, src))
			return n;

		fb_writew(v, dst);

		src++, dst++;
		n -= 2;
	}

	if (n) {
		u8 v;

		if (__get_user(v, ((u8 *) src)))
			return n;

		fb_writeb(v, dst);
	}
	return 0;
}