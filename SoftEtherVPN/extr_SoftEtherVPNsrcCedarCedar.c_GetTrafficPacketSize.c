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
typedef  scalar_t__ UINT64 ;
struct TYPE_6__ {scalar_t__ UnicastBytes; scalar_t__ BroadcastBytes; } ;
struct TYPE_5__ {scalar_t__ UnicastBytes; scalar_t__ BroadcastBytes; } ;
struct TYPE_7__ {TYPE_2__ Send; TYPE_1__ Recv; } ;
typedef  TYPE_3__ TRAFFIC ;

/* Variables and functions */

UINT64 GetTrafficPacketSize(TRAFFIC *t)
{
	// Validate arguments
	if (t == NULL)
	{
		return 0;
	}

	return t->Recv.BroadcastBytes + t->Recv.UnicastBytes +
		t->Send.BroadcastBytes + t->Send.UnicastBytes;
}