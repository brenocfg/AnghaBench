#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct et131x_adapter {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * Packet; } ;
typedef  TYPE_1__ MP_RFD ;

/* Variables and functions */

int et131x_rfd_resources_alloc(struct et131x_adapter *adapter, MP_RFD *pMpRfd)
{
	pMpRfd->Packet = NULL;

	return 0;
}