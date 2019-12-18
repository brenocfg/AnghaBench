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
struct TYPE_4__ {scalar_t__ scrub; } ;
struct TYPE_3__ {scalar_t__ scrub; } ;
struct pf_state {TYPE_2__ dst; TYPE_1__ src; } ;

/* Variables and functions */
 int /*<<< orphan*/  pf_state_scrub_pl ; 
 int /*<<< orphan*/  pool_put (int /*<<< orphan*/ *,scalar_t__) ; 

void
pf_normalize_tcp_cleanup(struct pf_state *state)
{
	if (state->src.scrub)
		pool_put(&pf_state_scrub_pl, state->src.scrub);
	if (state->dst.scrub)
		pool_put(&pf_state_scrub_pl, state->dst.scrub);

	/* Someday... flush the TCP segment reassembly descriptors. */
}