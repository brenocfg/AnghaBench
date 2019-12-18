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

/* Variables and functions */
 int async_wrap_skb (struct sk_buff*,int*,int) ; 

__attribute__((used)) static inline int mcs_wrap_sir_skb(struct sk_buff *skb, __u8 * buf)
{
	int wraplen;

	/* 2: full frame length, including "the length" */
	wraplen = async_wrap_skb(skb, buf + 2, 4094);

	wraplen += 2;
	buf[0] = wraplen & 0xff;
	buf[1] = (wraplen >> 8) & 0xff;

	return wraplen;
}