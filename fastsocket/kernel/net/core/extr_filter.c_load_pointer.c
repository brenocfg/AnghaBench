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

/* Variables and functions */
 int SKF_AD_OFF ; 
 void* __load_pointer (struct sk_buff*,int) ; 
 void* skb_header_pointer (struct sk_buff*,int,unsigned int,void*) ; 

__attribute__((used)) static inline void *load_pointer(struct sk_buff *skb, int k,
				 unsigned int size, void *buffer)
{
	if (k >= 0)
		return skb_header_pointer(skb, k, size, buffer);
	else {
		if (k >= SKF_AD_OFF)
			return NULL;
		return __load_pointer(skb, k);
	}
}