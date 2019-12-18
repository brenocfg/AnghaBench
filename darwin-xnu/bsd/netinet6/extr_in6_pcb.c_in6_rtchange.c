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
struct inpcb {int /*<<< orphan*/  in6p_route; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROUTE_RELEASE (int /*<<< orphan*/ *) ; 

void
in6_rtchange(struct inpcb *inp, int errno)
{
#pragma unused(errno)
	/*
	 * A new route can be allocated the next time
	 * output is attempted.
	 */
	ROUTE_RELEASE(&inp->in6p_route);
}