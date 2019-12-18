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
typedef  int u_int ;
typedef  int u_char ;
typedef  int asn_len_t ;

/* Variables and functions */
 int ASN_MAXLEN ; 
 int /*<<< orphan*/  asn_error (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static u_int
asn_put_len(u_char *ptr, asn_len_t len)
{
	u_int lenlen, lenlen1;
	asn_len_t tmp;

	if (len > ASN_MAXLEN) {
		asn_error(NULL, "encoding length too long: (%u)", len);
		return (0);
	}

	if (len <= 127) {
		if (ptr)
			*ptr++ = (u_char)len;
		return (1);
	} else {
		lenlen = 0;
		/* compute number of bytes for value (is at least 1) */
		for (tmp = len; tmp != 0; tmp >>= 8)
			lenlen++;
		if (ptr != NULL) {
			*ptr++ = (u_char)lenlen | 0x80;
			lenlen1 = lenlen;
			while (lenlen1-- > 0) {
				ptr[lenlen1] = len & 0xff;
				len >>= 8;
			}
		}
		return (lenlen + 1);
	}
}