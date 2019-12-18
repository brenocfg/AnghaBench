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
struct TYPE_2__ {int /*<<< orphan*/  out_ops; int /*<<< orphan*/  in_ops; } ;
struct pxa_ep {TYPE_1__ stats; } ;

/* Variables and functions */

__attribute__((used)) static void inc_ep_stats_reqs(struct pxa_ep *ep, int is_in)
{
	if (is_in)
		ep->stats.in_ops++;
	else
		ep->stats.out_ops++;
}