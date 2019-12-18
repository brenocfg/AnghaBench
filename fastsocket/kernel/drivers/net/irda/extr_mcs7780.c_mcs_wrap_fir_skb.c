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
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
typedef  int __u8 ;
typedef  int __u32 ;

/* Variables and functions */
 int crc32_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff const*,int*,int) ; 

__attribute__((used)) static unsigned mcs_wrap_fir_skb(const struct sk_buff *skb, __u8 *buf)
{
	unsigned int len = 0;
	__u32 fcs = ~(crc32_le(~0, skb->data, skb->len));

	/* add 2 bytes for length value and 4 bytes for fcs. */
	len = skb->len + 6;

	/* The mcs7780 requires that the first two bytes are the packet
	 * length in little endian order.  Note: the length value includes
	 * the two bytes for the length value itself.
	 */
	buf[0] = len & 0xff;
	buf[1] = (len >> 8) & 0xff;
	/* copy the data into the tx buffer. */
	skb_copy_from_linear_data(skb, buf + 2, skb->len);
	/* put the fcs in the last four bytes in little endian order. */
	buf[len - 4] = fcs & 0xff;
	buf[len - 3] = (fcs >> 8) & 0xff;
	buf[len - 2] = (fcs >> 16) & 0xff;
	buf[len - 1] = (fcs >> 24) & 0xff;

	return len;
}