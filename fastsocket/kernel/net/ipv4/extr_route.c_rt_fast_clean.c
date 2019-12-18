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
struct TYPE_5__ {scalar_t__ rt_next; } ;
struct TYPE_6__ {TYPE_2__ dst; } ;
struct TYPE_4__ {scalar_t__ iif; } ;
struct rtable {int rt_flags; TYPE_3__ u; TYPE_1__ fl; } ;

/* Variables and functions */
 int RTCF_BROADCAST ; 
 int RTCF_MULTICAST ; 

__attribute__((used)) static inline int rt_fast_clean(struct rtable *rth)
{
	/* Kill broadcast/multicast entries very aggresively, if they
	   collide in hash table with more useful entries */
	return (rth->rt_flags & (RTCF_BROADCAST | RTCF_MULTICAST)) &&
		rth->fl.iif && rth->u.dst.rt_next;
}