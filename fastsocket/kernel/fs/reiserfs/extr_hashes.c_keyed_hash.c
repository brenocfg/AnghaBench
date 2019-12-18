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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  FULLROUNDS ; 
 int /*<<< orphan*/  PARTROUNDS ; 
 int /*<<< orphan*/  TEACORE (int /*<<< orphan*/ ) ; 

u32 keyed_hash(const signed char *msg, int len)
{
	u32 k[] = { 0x9464a485, 0x542e1a94, 0x3e846bff, 0xb75bcfc3 };

	u32 h0 = k[0], h1 = k[1];
	u32 a, b, c, d;
	u32 pad;
	int i;

	//      assert(len >= 0 && len < 256);

	pad = (u32) len | ((u32) len << 8);
	pad |= pad << 16;

	while (len >= 16) {
		a = (u32) msg[0] |
		    (u32) msg[1] << 8 | (u32) msg[2] << 16 | (u32) msg[3] << 24;
		b = (u32) msg[4] |
		    (u32) msg[5] << 8 | (u32) msg[6] << 16 | (u32) msg[7] << 24;
		c = (u32) msg[8] |
		    (u32) msg[9] << 8 |
		    (u32) msg[10] << 16 | (u32) msg[11] << 24;
		d = (u32) msg[12] |
		    (u32) msg[13] << 8 |
		    (u32) msg[14] << 16 | (u32) msg[15] << 24;

		TEACORE(PARTROUNDS);

		len -= 16;
		msg += 16;
	}

	if (len >= 12) {
		a = (u32) msg[0] |
		    (u32) msg[1] << 8 | (u32) msg[2] << 16 | (u32) msg[3] << 24;
		b = (u32) msg[4] |
		    (u32) msg[5] << 8 | (u32) msg[6] << 16 | (u32) msg[7] << 24;
		c = (u32) msg[8] |
		    (u32) msg[9] << 8 |
		    (u32) msg[10] << 16 | (u32) msg[11] << 24;

		d = pad;
		for (i = 12; i < len; i++) {
			d <<= 8;
			d |= msg[i];
		}
	} else if (len >= 8) {
		a = (u32) msg[0] |
		    (u32) msg[1] << 8 | (u32) msg[2] << 16 | (u32) msg[3] << 24;
		b = (u32) msg[4] |
		    (u32) msg[5] << 8 | (u32) msg[6] << 16 | (u32) msg[7] << 24;

		c = d = pad;
		for (i = 8; i < len; i++) {
			c <<= 8;
			c |= msg[i];
		}
	} else if (len >= 4) {
		a = (u32) msg[0] |
		    (u32) msg[1] << 8 | (u32) msg[2] << 16 | (u32) msg[3] << 24;

		b = c = d = pad;
		for (i = 4; i < len; i++) {
			b <<= 8;
			b |= msg[i];
		}
	} else {
		a = b = c = d = pad;
		for (i = 0; i < len; i++) {
			a <<= 8;
			a |= msg[i];
		}
	}

	TEACORE(FULLROUNDS);

/*	return 0;*/
	return h0 ^ h1;
}