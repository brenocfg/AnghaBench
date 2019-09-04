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
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  ifnet_ctl_cmd_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 

__attribute__((used)) static errno_t
ifp_if_ctl(struct ifnet *ifp, ifnet_ctl_cmd_t cmd, u_int32_t arglen, void *arg)
{
#pragma unused(ifp, cmd, arglen, arg)
	return (EOPNOTSUPP);
}