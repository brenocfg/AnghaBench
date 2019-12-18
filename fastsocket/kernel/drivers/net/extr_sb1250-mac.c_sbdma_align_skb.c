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
struct sk_buff {unsigned char* data; } ;

/* Variables and functions */
 unsigned char* PTR_ALIGN (unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static inline void sbdma_align_skb(struct sk_buff *skb,
				   unsigned int power2, unsigned int offset)
{
	unsigned char *addr = skb->data;
	unsigned char *newaddr = PTR_ALIGN(addr, power2);

	skb_reserve(skb, newaddr - addr + offset);
}