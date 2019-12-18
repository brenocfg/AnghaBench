#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ UnicastCount; scalar_t__ UnicastBytes; scalar_t__ BroadcastCount; scalar_t__ BroadcastBytes; } ;
struct TYPE_6__ {scalar_t__ UnicastCount; scalar_t__ UnicastBytes; scalar_t__ BroadcastCount; scalar_t__ BroadcastBytes; } ;
struct TYPE_8__ {TYPE_2__ Send; TYPE_1__ Recv; } ;
typedef  TYPE_3__ TRAFFIC ;

/* Variables and functions */

void AddTraffic(TRAFFIC *dst, TRAFFIC *diff)
{
	// Validate arguments
	if (dst == NULL || diff == NULL)
	{
		return;
	}

	dst->Recv.BroadcastBytes += diff->Recv.BroadcastBytes;
	dst->Recv.BroadcastCount += diff->Recv.BroadcastCount;
	dst->Recv.UnicastBytes += diff->Recv.UnicastBytes;
	dst->Recv.UnicastCount += diff->Recv.UnicastCount;

	dst->Send.BroadcastBytes += diff->Send.BroadcastBytes;
	dst->Send.BroadcastCount += diff->Send.BroadcastCount;
	dst->Send.UnicastBytes += diff->Send.UnicastBytes;
	dst->Send.UnicastCount += diff->Send.UnicastCount;
}