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
struct if_llreach {int dummy; } ;

/* Variables and functions */
 int iflr_reachable (struct if_llreach*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ifnet_llreach_reachable(struct if_llreach *lr)
{
	/*
	 * Check whether the cache is too old to be trusted.
	 */
	return (iflr_reachable(lr, 0, 0));
}