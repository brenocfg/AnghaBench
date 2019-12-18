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
struct rubin_state {scalar_t__* bits; scalar_t__ bit_divider; } ;

/* Variables and functions */
 int encode (struct rubin_state*,scalar_t__,scalar_t__,unsigned char) ; 

__attribute__((used)) static int out_byte(struct rubin_state *rs, unsigned char byte)
{
	int i, ret;
	struct rubin_state rs_copy;
	rs_copy = *rs;

	for (i=0; i<8; i++) {
		ret = encode(rs, rs->bit_divider-rs->bits[i],
			     rs->bits[i], byte & 1);
		if (ret) {
			/* Failed. Restore old state */
			*rs = rs_copy;
			return ret;
		}
		byte >>= 1 ;
	}
	return 0;
}