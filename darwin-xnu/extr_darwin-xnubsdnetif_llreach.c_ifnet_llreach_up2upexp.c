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
typedef  scalar_t__ u_int64_t ;
struct if_llreach {scalar_t__ lr_reachable; } ;

/* Variables and functions */

u_int64_t
ifnet_llreach_up2upexp(struct if_llreach *lr, u_int64_t uptime)
{
	return (lr->lr_reachable + uptime);
}