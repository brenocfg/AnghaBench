#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {void* handle; } ;

/* Variables and functions */
 TYPE_1__* TIPC_SKB_CB (struct sk_buff*) ; 

__attribute__((used)) static void bcbuf_set_acks(struct sk_buff *buf, u32 acks)
{
	TIPC_SKB_CB(buf)->handle = (void *)(unsigned long)acks;
}