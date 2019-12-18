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
struct nd_prefix {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int nd6_prefix_onlink_common (struct nd_prefix*,int /*<<< orphan*/ ,unsigned int) ; 

int
nd6_prefix_onlink_scoped(struct nd_prefix *pr, unsigned int ifscope)
{
	return (nd6_prefix_onlink_common(pr, TRUE, ifscope));
}