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
struct socket {int /*<<< orphan*/  so_flags; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  SOF_MULTIPAGES ; 

void
somultipages(struct socket *so, boolean_t set)
{
	if (set)
		so->so_flags |= SOF_MULTIPAGES;
	else
		so->so_flags &= ~SOF_MULTIPAGES;
}