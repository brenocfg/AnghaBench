#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT64 ;
struct TYPE_11__ {int Value; } ;
struct TYPE_13__ {TYPE_3__ UploadLimiter; } ;
struct TYPE_12__ {TYPE_1__* Policy; TYPE_2__* PacketAdapter; } ;
struct TYPE_10__ {scalar_t__ Param; } ;
struct TYPE_9__ {int MaxUpload; } ;
typedef  TYPE_3__ TRAFFIC_LIMITER ;
typedef  TYPE_4__ SESSION ;
typedef  int /*<<< orphan*/  PKT ;
typedef  TYPE_5__ HUB_PA ;

/* Variables and functions */
 int /*<<< orphan*/  IntoTrafficLimiter (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ IsMostHighestPriorityPacket (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ LIMITER_SAMPLING_SPAN ; 

bool StorePacketFilterByTrafficLimiter(SESSION *s, PKT *p)
{
	HUB_PA *pa;
	TRAFFIC_LIMITER *tr;
	// Validate arguments
	if (s == NULL || p == NULL)
	{
		return false;
	}

	if (s->Policy->MaxUpload == 0)
	{
		// Unlimited
		return true;
	}

	pa = (HUB_PA *)s->PacketAdapter->Param;
	tr = &pa->UploadLimiter;

	// Restrictions are not applied for priority packets
	if (IsMostHighestPriorityPacket(s, p))
	{
		return true;
	}

	// Input packets to the limiter
	IntoTrafficLimiter(tr, p);

	// Compare the current bandwidth and limit value
	if ((tr->Value * (UINT64)1000 / (UINT64)LIMITER_SAMPLING_SPAN) > s->Policy->MaxUpload)
	{
		// Discard the packet
		return false;
	}

	return true;
}