#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
typedef  int /*<<< orphan*/  PPP_SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  PPPRecvResponsePacket (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

USHORT PPPContinueCurrentProtocolRequestListening(PPP_SESSION *p, USHORT protocol)
{
	USHORT received_protocol = 0;
	// Validate arguments
	if (p == NULL)
	{
		return 0;
	}

	PPPRecvResponsePacket(p, NULL, protocol, &received_protocol, false, false);

	return received_protocol;
}