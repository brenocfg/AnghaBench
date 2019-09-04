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
struct kev_msg {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
ifp_if_event(struct ifnet *ifp, const struct kev_msg *e)
{
#pragma unused(ifp, e)
}