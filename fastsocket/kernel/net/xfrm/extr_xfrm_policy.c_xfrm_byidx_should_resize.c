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
struct TYPE_2__ {unsigned int policy_idx_hmask; } ;
struct net {TYPE_1__ xfrm; } ;

/* Variables and functions */
 unsigned int xfrm_policy_hashmax ; 

__attribute__((used)) static inline int xfrm_byidx_should_resize(struct net *net, int total)
{
	unsigned int hmask = net->xfrm.policy_idx_hmask;

	if ((hmask + 1) < xfrm_policy_hashmax &&
	    total > hmask)
		return 1;

	return 0;
}