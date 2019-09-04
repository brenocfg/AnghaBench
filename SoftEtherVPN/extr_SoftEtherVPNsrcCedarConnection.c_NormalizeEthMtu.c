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
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_8__ {scalar_t__ LastChangeMtuError; int /*<<< orphan*/  Name; int /*<<< orphan*/  Eth; } ;
struct TYPE_7__ {TYPE_1__* Session; } ;
struct TYPE_6__ {int /*<<< orphan*/  Name; int /*<<< orphan*/  Hub; } ;
typedef  TYPE_2__ CONNECTION ;
typedef  TYPE_3__ BRIDGE ;

/* Variables and functions */
 scalar_t__ EthGetMtu (int /*<<< orphan*/ ) ; 
 scalar_t__ EthIsChangeMtuSupported (int /*<<< orphan*/ ) ; 
 int EthSetMtu (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ Tick64 () ; 

void NormalizeEthMtu(BRIDGE *b, CONNECTION *c, UINT packet_size)
{
	// Validate arguments
	if (packet_size == 0 || b == NULL || c == NULL)
	{
		return;
	}

	// Raise the MTU when the packet exceeds the current MTU
	if (EthIsChangeMtuSupported(b->Eth))
	{
		UINT currentMtu = EthGetMtu(b->Eth);
		if (currentMtu != 0)
		{
			if (packet_size > currentMtu)
			{
				bool ok = EthSetMtu(b->Eth, packet_size);

				if (ok)
				{
					HLog(c->Session->Hub, "LH_SET_MTU", c->Session->Name,
						b->Name, currentMtu, packet_size, packet_size);
				}
				else
				{
					UINT64 now = Tick64();

					if (b->LastChangeMtuError == 0 ||
						now >= (b->LastChangeMtuError + 60000ULL))
					{
						HLog(c->Session->Hub, "LH_SET_MTU_ERROR", c->Session->Name,
							b->Name, currentMtu, packet_size, packet_size);

						b->LastChangeMtuError = now;
					}
				}
			}
		}
	}
}