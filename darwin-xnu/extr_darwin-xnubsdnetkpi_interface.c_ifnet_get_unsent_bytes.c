#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
typedef  TYPE_1__* ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_4__ {int if_eflags; int /*<<< orphan*/  if_snd; scalar_t__ if_sndbyte_unsent; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 scalar_t__ IFCQ_BYTES (int /*<<< orphan*/ *) ; 
 int IFEF_TXSTART ; 
 int /*<<< orphan*/  IF_FULLY_ATTACHED (TYPE_1__*) ; 

errno_t
ifnet_get_unsent_bytes(ifnet_t interface, int64_t *unsent_bytes)
{
	int64_t bytes;

	if (interface == NULL || unsent_bytes == NULL)
		return (EINVAL);

	bytes = *unsent_bytes = 0;

	if (!IF_FULLY_ATTACHED(interface))
		return (ENXIO);

	bytes = interface->if_sndbyte_unsent;

	if (interface->if_eflags & IFEF_TXSTART)
		bytes += IFCQ_BYTES(&interface->if_snd);
	*unsent_bytes = bytes;

	return (0);
}