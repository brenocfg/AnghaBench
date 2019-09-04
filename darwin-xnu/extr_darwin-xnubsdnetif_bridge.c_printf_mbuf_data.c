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
typedef  scalar_t__ mbuf_t ;

/* Variables and functions */
 unsigned char* mbuf_data (scalar_t__) ; 
 size_t mbuf_len (scalar_t__) ; 
 scalar_t__ mbuf_next (scalar_t__) ; 
 size_t mbuf_pkthdr_len (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,unsigned char,char*) ; 

void
printf_mbuf_data(mbuf_t m, size_t offset, size_t len)
{
	mbuf_t			n;
	size_t			i, j;
	size_t			pktlen, mlen, maxlen;
	unsigned char	*ptr;

	pktlen = mbuf_pkthdr_len(m);

	if (offset > pktlen)
		return;

	maxlen = (pktlen - offset > len) ? len : pktlen - offset;
	n = m;
	mlen = mbuf_len(n);
	ptr = mbuf_data(n);
	for (i = 0, j = 0; i < maxlen; i++, j++) {
		if (j >= mlen) {
			n = mbuf_next(n);
			if (n == 0)
				break;
			ptr = mbuf_data(n);
			mlen = mbuf_len(n);
			j = 0;
		}
		if (i >= offset) {
			printf("%02x%s", ptr[j], i % 2 ? " " : "");
		}
	}
}