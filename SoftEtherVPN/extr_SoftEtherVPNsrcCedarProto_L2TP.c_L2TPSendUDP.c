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
typedef  int /*<<< orphan*/  UDPPACKET ;
struct TYPE_3__ {int /*<<< orphan*/  SendPacketList; } ;
typedef  TYPE_1__ L2TP_SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void L2TPSendUDP(L2TP_SERVER *l2tp, UDPPACKET *p)
{
	// Validate arguments
	if (l2tp == NULL || p == NULL)
	{
		return;
	}

	Add(l2tp->SendPacketList, p);
}