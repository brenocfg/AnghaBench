#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ip6asfrag {TYPE_2__* ip6af_up; TYPE_1__* ip6af_down; } ;
struct TYPE_4__ {TYPE_1__* ip6af_down; } ;
struct TYPE_3__ {TYPE_2__* ip6af_up; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  ip6qlock ; 

void
frag6_deq(struct ip6asfrag *af6)
{
	LCK_MTX_ASSERT(&ip6qlock, LCK_MTX_ASSERT_OWNED);

	af6->ip6af_up->ip6af_down = af6->ip6af_down;
	af6->ip6af_down->ip6af_up = af6->ip6af_up;
}