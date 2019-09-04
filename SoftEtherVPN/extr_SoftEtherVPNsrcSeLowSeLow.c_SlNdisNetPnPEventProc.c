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
struct TYPE_7__ {int IsEnumCompleted; } ;
struct TYPE_5__ {scalar_t__ NetEvent; } ;
struct TYPE_6__ {TYPE_1__ NetPnPEvent; } ;
typedef  int /*<<< orphan*/  SL_ADAPTER ;
typedef  TYPE_2__ NET_PNP_EVENT_NOTIFICATION ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;
typedef  scalar_t__ NDIS_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 scalar_t__ NetEventBindsComplete ; 
 TYPE_3__* sl ; 

NDIS_STATUS SlNdisNetPnPEventProc(NDIS_HANDLE protocol_binding_context, NET_PNP_EVENT_NOTIFICATION *net_pnp_event)
{
	SL_ADAPTER *a = (SL_ADAPTER *)protocol_binding_context;

	if (net_pnp_event != NULL)
	{
		if (net_pnp_event->NetPnPEvent.NetEvent == NetEventBindsComplete)
		{
			sl->IsEnumCompleted = true;
		}
	}

	return NDIS_STATUS_SUCCESS;
}