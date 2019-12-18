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
struct netns_frags {scalar_t__ low_thresh; } ;
struct inet_frags {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  inet_frag_evictor (struct netns_frags*,struct inet_frags*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 

void inet_frags_exit_net(struct netns_frags *nf, struct inet_frags *f)
{
	nf->low_thresh = 0;

	local_bh_disable();
	inet_frag_evictor(nf, f);
	local_bh_enable();
}