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
 int irda_get_mtt (struct sk_buff*) ; 

__attribute__((used)) static __u8 get_turnaround_time(struct sk_buff *skb)
{
	int turnaround_time = irda_get_mtt(skb);

	if ( turnaround_time == 0 )
		return 0;
	else if ( turnaround_time <= 10 )
		return 1;
	else if ( turnaround_time <= 50 )
		return 2;
	else if ( turnaround_time <= 100 )
		return 3;
	else if ( turnaround_time <= 500 )
		return 4;
	else if ( turnaround_time <= 1000 )
		return 5;
	else if ( turnaround_time <= 5000 )
		return 6;
	else
		return 7;
}