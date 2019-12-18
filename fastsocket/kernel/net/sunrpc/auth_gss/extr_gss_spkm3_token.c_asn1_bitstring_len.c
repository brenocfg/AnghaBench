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
struct xdr_netobj {int len; char* data; } ;

/* Variables and functions */

void
asn1_bitstring_len(struct xdr_netobj *in, int *enclen, int *zerobits)
{
	int i, zbit = 0,elen = in->len;
	char *ptr;

	ptr = &in->data[in->len -1];

	/* count trailing 0's */
	for(i = in->len; i > 0; i--) {
		if (*ptr == 0) {
			ptr--;
			elen--;
		} else
			break;
	}

	/* count number of 0 bits in final octet */
	ptr = &in->data[elen - 1];
	for(i = 0; i < 8; i++) {
		short mask = 0x01;

		if (!((mask << i) & *ptr))
			zbit++;
		else
			break;
	}
	*enclen = elen;
	*zerobits = zbit;
}