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
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* __dev_alloc_skb (unsigned int,int /*<<< orphan*/ ) ; 

struct sk_buff *dev_alloc_skb(unsigned int length)
{
	/*
	 * There is more code here than it seems:
	 * __dev_alloc_skb is an inline
	 */
	return __dev_alloc_skb(length, GFP_ATOMIC);
}