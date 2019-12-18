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
struct sk_buff {int dummy; } ;
typedef  int __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 int STIR_FIFO_SIZE ; 
 int STIR_IRDA_HEADER ; 
 int async_wrap_skb (struct sk_buff*,int*,int) ; 

__attribute__((used)) static unsigned wrap_sir_skb(struct sk_buff *skb, __u8 *buf)
{
	__u16 wraplen;

	wraplen = async_wrap_skb(skb, buf + STIR_IRDA_HEADER,
				 STIR_FIFO_SIZE - STIR_IRDA_HEADER);
	buf[0] = 0x55;
	buf[1] = 0xAA;
	buf[2] = wraplen & 0xff;
	buf[3] = (wraplen >> 8) & 0xff;

	return wraplen + STIR_IRDA_HEADER;
}