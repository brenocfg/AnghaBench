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
struct sk_buff {int* data; int len; } ;
typedef  int __u8 ;
typedef  int __u32 ;
typedef  int __u16 ;

/* Variables and functions */
 int STIR_IRDA_HEADER ; 
 int crc32_le (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int* stuff_fir (int*,int) ; 

__attribute__((used)) static unsigned wrap_fir_skb(const struct sk_buff *skb, __u8 *buf)
{
	__u8 *ptr = buf;
	__u32 fcs = ~(crc32_le(~0, skb->data, skb->len));
	__u16 wraplen;
	int i;

	/* Header */
	buf[0] = 0x55;
	buf[1] = 0xAA;

	ptr = buf + STIR_IRDA_HEADER;
	memset(ptr, 0x7f, 16);
	ptr += 16;

	/* BOF */
	*ptr++  = 0x7e;
	*ptr++  = 0x7e;

	/* Address / Control / Information */
	for (i = 0; i < skb->len; i++)
		ptr = stuff_fir(ptr, skb->data[i]);

	/* FCS */
	ptr = stuff_fir(ptr, fcs & 0xff);
	ptr = stuff_fir(ptr, (fcs >> 8) & 0xff);
	ptr = stuff_fir(ptr, (fcs >> 16) & 0xff);
	ptr = stuff_fir(ptr, (fcs >> 24) & 0xff);

	/* EOFs */
	*ptr++ = 0x7e;
	*ptr++ = 0x7e;

	/* Total length, minus the header */
	wraplen = (ptr - buf) - STIR_IRDA_HEADER;
	buf[2] = wraplen & 0xff;
	buf[3] = (wraplen >> 8) & 0xff;

	return wraplen + STIR_IRDA_HEADER;
}