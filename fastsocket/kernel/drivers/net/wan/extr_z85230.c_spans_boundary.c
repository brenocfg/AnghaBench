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
struct sk_buff {unsigned long len; scalar_t__ data; } ;

/* Variables and functions */

__attribute__((used)) static inline int spans_boundary(struct sk_buff *skb)
{
	unsigned long a=(unsigned long)skb->data;
	a^=(a+skb->len);
	if(a&0x00010000)	/* If the 64K bit is different.. */
		return 1;
	return 0;
}