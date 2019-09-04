#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
struct TYPE_6__ {scalar_t__ PacketSize; } ;
struct TYPE_5__ {scalar_t__ LastTime; scalar_t__ Value; } ;
typedef  TYPE_1__ TRAFFIC_LIMITER ;
typedef  TYPE_2__ PKT ;

/* Variables and functions */
 scalar_t__ LIMITER_SAMPLING_SPAN ; 
 scalar_t__ Tick64 () ; 

void IntoTrafficLimiter(TRAFFIC_LIMITER *tr, PKT *p)
{
	UINT64 now = Tick64();
	// Validate arguments
	if (tr == NULL || p == NULL)
	{
		return;
	}

	if (tr->LastTime == 0 || tr->LastTime > now ||
		(tr->LastTime + LIMITER_SAMPLING_SPAN) < now)
	{
		// Sampling initialization
		tr->Value = 0;
		tr->LastTime = now;
	}

	// Value increase
	tr->Value += p->PacketSize * (UINT64)8;
}