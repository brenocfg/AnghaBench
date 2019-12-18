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
 int br_sslio_read (int /*<<< orphan*/ *,unsigned char*,size_t) ; 

int
br_sslio_read_all(br_sslio_context *ctx, void *dst, size_t len)
{
	unsigned char *buf;

	buf = dst;
	while (len > 0) {
		int rlen;

		rlen = br_sslio_read(ctx, buf, len);
		if (rlen < 0) {
			return -1;
		}
		buf += rlen;
		len -= (size_t)rlen;
	}
	return 0;
}