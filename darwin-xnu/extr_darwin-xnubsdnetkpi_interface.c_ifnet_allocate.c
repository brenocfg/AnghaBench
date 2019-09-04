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
struct ifnet_init_params {int dummy; } ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  ifnet_allocate_common (struct ifnet_init_params const*,int /*<<< orphan*/ *,int) ; 

errno_t
ifnet_allocate(const struct ifnet_init_params *init, ifnet_t *ifp)
{
	return (ifnet_allocate_common(init, ifp, false));
}