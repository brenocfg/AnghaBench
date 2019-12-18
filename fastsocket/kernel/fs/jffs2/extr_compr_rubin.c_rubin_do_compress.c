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
typedef  int uint32_t ;
struct rubin_state {int /*<<< orphan*/  pp; } ;

/* Variables and functions */
 int /*<<< orphan*/  end_rubin (struct rubin_state*) ; 
 int /*<<< orphan*/  init_pushpull (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_rubin (struct rubin_state*,int,int*) ; 
 int /*<<< orphan*/  out_byte (struct rubin_state*,unsigned char) ; 
 int pushedbits (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rubin_do_compress(int bit_divider, int *bits, unsigned char *data_in,
			     unsigned char *cpage_out, uint32_t *sourcelen,
			     uint32_t *dstlen)
	{
	int outpos = 0;
	int pos=0;
	struct rubin_state rs;

	init_pushpull(&rs.pp, cpage_out, *dstlen * 8, 0, 32);

	init_rubin(&rs, bit_divider, bits);

	while (pos < (*sourcelen) && !out_byte(&rs, data_in[pos]))
		pos++;

	end_rubin(&rs);

	if (outpos > pos) {
		/* We failed */
		return -1;
	}

	/* Tell the caller how much we managed to compress,
	 * and how much space it took */

	outpos = (pushedbits(&rs.pp)+7)/8;

	if (outpos >= pos)
		return -1; /* We didn't actually compress */
	*sourcelen = pos;
	*dstlen = outpos;
	return 0;
}