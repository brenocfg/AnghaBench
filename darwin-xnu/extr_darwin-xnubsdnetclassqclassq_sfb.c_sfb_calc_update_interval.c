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
typedef  int /*<<< orphan*/  u_int64_t ;
struct sfb {int /*<<< orphan*/  sfb_update_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  ifclassq_calc_update_interval (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_nsectimer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sfb_calc_update_interval(struct sfb *sp, u_int64_t out_bw)
{
#pragma unused(out_bw)
	u_int64_t update_interval = 0;
	ifclassq_calc_update_interval(&update_interval);
	net_nsectimer(&update_interval, &sp->sfb_update_interval);
}