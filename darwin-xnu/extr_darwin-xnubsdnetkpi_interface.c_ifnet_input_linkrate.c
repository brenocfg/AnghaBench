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
typedef  int /*<<< orphan*/  u_int64_t ;
struct TYPE_2__ {int /*<<< orphan*/  eff_bw; } ;
struct ifnet {TYPE_1__ if_input_bw; } ;

/* Variables and functions */

u_int64_t
ifnet_input_linkrate(struct ifnet *ifp)
{
	return (ifp->if_input_bw.eff_bw);
}