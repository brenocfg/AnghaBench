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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;
typedef  int /*<<< orphan*/  NDIS_PACKET ;
typedef  int /*<<< orphan*/  NDIS_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  NDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  NeoNdisSendPackets (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 

NDIS_STATUS NeoNdisSend(NDIS_HANDLE MiniportAdapterContext,
						NDIS_PACKET *Packet, UINT Flags)
{
	NDIS_PACKET *PacketArray[1];
	PacketArray[0] = Packet;
	NeoNdisSendPackets(MiniportAdapterContext, PacketArray, 1);

	return NDIS_STATUS_SUCCESS;
}