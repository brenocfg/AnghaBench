#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  TYPE_1__* ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_5__ {int /*<<< orphan*/  if_linkmiblen; void* if_linkmib; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ifnet_lock_done (TYPE_1__*) ; 
 int /*<<< orphan*/  ifnet_lock_exclusive (TYPE_1__*) ; 

errno_t
ifnet_set_link_mib_data(ifnet_t interface, void *mibData, u_int32_t mibLen)
{
	if (interface == NULL)
		return (EINVAL);

	ifnet_lock_exclusive(interface);
	interface->if_linkmib = (void*)mibData;
	interface->if_linkmiblen = mibLen;
	ifnet_lock_done(interface);
	return (0);
}