#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  iif; } ;
struct TYPE_4__ {int lastuse; } ;
struct TYPE_5__ {TYPE_1__ dst; } ;
struct rtable {int rt_flags; TYPE_3__ fl; TYPE_2__ u; } ;

/* Variables and functions */
 int RTCF_BROADCAST ; 
 int RTCF_LOCAL ; 
 int RTCF_MULTICAST ; 
 int jiffies ; 
 scalar_t__ rt_valuable (struct rtable*) ; 

__attribute__((used)) static inline u32 rt_score(struct rtable *rt)
{
	u32 score = jiffies - rt->u.dst.lastuse;

	score = ~score & ~(3<<30);

	if (rt_valuable(rt))
		score |= (1<<31);

	if (!rt->fl.iif ||
	    !(rt->rt_flags & (RTCF_BROADCAST|RTCF_MULTICAST|RTCF_LOCAL)))
		score |= (1<<30);

	return score;
}