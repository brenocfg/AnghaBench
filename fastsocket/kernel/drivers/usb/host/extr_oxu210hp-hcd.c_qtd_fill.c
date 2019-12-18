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
typedef  int u64 ;
typedef  int u32 ;
struct ehci_qtd {int length; void* hw_token; void** hw_buf_hi; void** hw_buf; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 void* cpu_to_le32 (int) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int qtd_fill(struct ehci_qtd *qtd, dma_addr_t buf, size_t len,
				int token, int maxpacket)
{
	int i, count;
	u64 addr = buf;

	/* one buffer entry per 4K ... first might be short or unaligned */
	qtd->hw_buf[0] = cpu_to_le32((u32)addr);
	qtd->hw_buf_hi[0] = cpu_to_le32((u32)(addr >> 32));
	count = 0x1000 - (buf & 0x0fff);	/* rest of that page */
	if (likely(len < count))		/* ... iff needed */
		count = len;
	else {
		buf +=  0x1000;
		buf &= ~0x0fff;

		/* per-qtd limit: from 16K to 20K (best alignment) */
		for (i = 1; count < len && i < 5; i++) {
			addr = buf;
			qtd->hw_buf[i] = cpu_to_le32((u32)addr);
			qtd->hw_buf_hi[i] = cpu_to_le32((u32)(addr >> 32));
			buf += 0x1000;
			if ((count + 0x1000) < len)
				count += 0x1000;
			else
				count = len;
		}

		/* short packets may only terminate transfers */
		if (count != len)
			count -= (count % maxpacket);
	}
	qtd->hw_token = cpu_to_le32((count << 16) | token);
	qtd->length = count;

	return count;
}