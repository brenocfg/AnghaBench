#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ifnet_t ;
struct TYPE_8__ {scalar_t__ buf_interface; int buf_sndbuf; } ;
typedef  TYPE_2__ ifnet_buffer_status_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_7__ {int if_eflags; scalar_t__ if_sndbyte_unsent; int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 scalar_t__ IFCQ_BYTES (int /*<<< orphan*/ *) ; 
 int IFEF_TXSTART ; 
 int /*<<< orphan*/  IF_FULLY_ATTACHED (TYPE_1__* const) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 

errno_t
ifnet_get_buffer_status(const ifnet_t ifp, ifnet_buffer_status_t *buf_status)
{
	if (ifp == NULL || buf_status == NULL)
		return (EINVAL);

	bzero(buf_status, sizeof (*buf_status));

	if (!IF_FULLY_ATTACHED(ifp))
		return (ENXIO);

	if (ifp->if_eflags & IFEF_TXSTART)
		buf_status->buf_interface = IFCQ_BYTES(&ifp->if_snd);

	buf_status->buf_sndbuf = ((buf_status->buf_interface != 0) ||
	    (ifp->if_sndbyte_unsent != 0)) ? 1 : 0;

	return (0);
}