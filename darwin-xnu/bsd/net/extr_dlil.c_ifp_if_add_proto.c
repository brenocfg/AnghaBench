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
typedef  int /*<<< orphan*/  u_int32_t ;
struct ifnet_demux_desc {int dummy; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  protocol_family_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 

__attribute__((used)) static errno_t
ifp_if_add_proto(struct ifnet *ifp, protocol_family_t pf,
    const struct ifnet_demux_desc *da, u_int32_t dc)
{
#pragma unused(ifp, pf, da, dc)
	return (EINVAL);
}