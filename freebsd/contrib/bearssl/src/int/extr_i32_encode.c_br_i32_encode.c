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

/* Variables and functions */
 int /*<<< orphan*/  br_enc32be (unsigned char*,int const) ; 

void
br_i32_encode(void *dst, size_t len, const uint32_t *x)
{
	unsigned char *buf;
	size_t k;

	buf = dst;

	/*
	 * Compute the announced size of x in bytes; extra bytes are
	 * filled with zeros.
	 */
	k = (x[0] + 7) >> 3;
	while (len > k) {
		*buf ++ = 0;
		len --;
	}

	/*
	 * Now we use k as index within x[]. That index starts at 1;
	 * we initialize it to the topmost complete word, and process
	 * any remaining incomplete word.
	 */
	k = (len + 3) >> 2;
	switch (len & 3) {
	case 3:
		*buf ++ = x[k] >> 16;
		/* fall through */
	case 2:
		*buf ++ = x[k] >> 8;
		/* fall through */
	case 1:
		*buf ++ = x[k];
		k --;
	}

	/*
	 * Encode all complete words.
	 */
	while (k > 0) {
		br_enc32be(buf, x[k]);
		k --;
		buf += 4;
	}
}