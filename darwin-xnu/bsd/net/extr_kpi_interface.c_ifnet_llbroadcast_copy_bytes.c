#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  buffer; } ;
struct TYPE_6__ {size_t length; TYPE_1__ u; } ;
struct TYPE_7__ {TYPE_2__ if_broadcast; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EMSGSIZE ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,void*,int) ; 

errno_t
ifnet_llbroadcast_copy_bytes(ifnet_t interface, void *addr, size_t buffer_len,
    size_t *out_len)
{
	if (interface == NULL || addr == NULL || out_len == NULL)
		return (EINVAL);

	*out_len = interface->if_broadcast.length;

	if (buffer_len < interface->if_broadcast.length)
		return (EMSGSIZE);

	if (interface->if_broadcast.length == 0)
		return (ENXIO);

	if (interface->if_broadcast.length <=
	    sizeof (interface->if_broadcast.u.buffer)) {
		bcopy(interface->if_broadcast.u.buffer, addr,
		    interface->if_broadcast.length);
	} else {
		bcopy(interface->if_broadcast.u.ptr, addr,
		    interface->if_broadcast.length);
	}

	return (0);
}