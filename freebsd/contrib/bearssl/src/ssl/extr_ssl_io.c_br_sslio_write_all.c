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
typedef  int /*<<< orphan*/  br_sslio_context ;

/* Variables and functions */
 int br_sslio_write (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

int
br_sslio_write_all(br_sslio_context *ctx, const void *src, size_t len)
{
	const unsigned char *buf;

	buf = src;
	while (len > 0) {
		int wlen;

		wlen = br_sslio_write(ctx, buf, len);
		if (wlen < 0) {
			return -1;
		}
		buf += wlen;
		len -= (size_t)wlen;
	}
	return 0;
}