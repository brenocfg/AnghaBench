#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * LastStoredPacket; } ;
typedef  TYPE_1__ PPP_SESSION ;
typedef  int /*<<< orphan*/  PPP_PACKET ;

/* Variables and functions */
 int /*<<< orphan*/ * PPPRecvPacketWithLowLayerProcessing (TYPE_1__*,int) ; 

PPP_PACKET *PPPRecvPacketForCommunication(PPP_SESSION *p)
{
	// Validate arguments
	if (p == NULL)
	{
		return NULL;
	}

	if (p->LastStoredPacket != NULL)
	{
		PPP_PACKET *pp = p->LastStoredPacket;
		p->LastStoredPacket = NULL;
		return pp;
	}

	return PPPRecvPacketWithLowLayerProcessing(p, true);
}