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
typedef  int __u16 ;

/* Variables and functions */
 int irda_calc_crc16 (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff const*,int*,int) ; 

__attribute__((used)) static unsigned mcs_wrap_mir_skb(const struct sk_buff *skb, __u8 *buf)
{
	__u16 fcs = 0;
	int len = skb->len + 4;

	fcs = ~(irda_calc_crc16(~fcs, skb->data, skb->len));
	/* put the total packet length in first.  Note: packet length
	 * value includes the two bytes that hold the packet length
	 * itself.
	 */
	buf[0] = len & 0xff;
	buf[1] = (len >> 8) & 0xff;
	/* copy the data */
	skb_copy_from_linear_data(skb, buf + 2, skb->len);
	/* put the fcs in last two bytes in little endian order. */
	buf[len - 2] = fcs & 0xff;
	buf[len - 1] = (fcs >> 8) & 0xff;

	return len;
}