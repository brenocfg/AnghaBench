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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ mbuf_t ;

/* Variables and functions */
 scalar_t__ mbuf_data (scalar_t__) ; 
 size_t mbuf_len (scalar_t__) ; 
 scalar_t__ mbuf_next (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
printmbuf(const char *str, mbuf_t mb, uint32_t offset, uint32_t len)
{
	size_t i;
	int cout = 1;

	len = len ? len : ~0;
	printf("%s mbuf = %p offset = %d len = %d:\n", str ? str : "mbuf", mb, offset, len);
	for (; mb && len; mb = mbuf_next(mb)) {
		if (offset >= mbuf_len(mb)) {
			offset -= mbuf_len(mb);
			continue;
		}
		for(i = offset; len && i < mbuf_len(mb); i++) {
			const char *s = (cout % 8) ? " " : (cout % 16) ? "    " : "\n";
			printf("%02x%s", ((uint8_t *)mbuf_data(mb))[i], s);
			len--;
			cout++;
		}
		offset = 0;
	}
	if ((cout-1) % 16)
		printf("\n");
	printf("Count chars %d\n", cout - 1);
}