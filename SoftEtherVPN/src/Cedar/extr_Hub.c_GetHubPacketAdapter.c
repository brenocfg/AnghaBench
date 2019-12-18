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
typedef  int /*<<< orphan*/  PACKET_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  HubPaFree ; 
 int /*<<< orphan*/  HubPaGetCancel ; 
 int /*<<< orphan*/  HubPaGetNextPacket ; 
 int /*<<< orphan*/  HubPaInit ; 
 int /*<<< orphan*/  HubPaPutPacket ; 
 int /*<<< orphan*/ * NewPacketAdapter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

PACKET_ADAPTER *GetHubPacketAdapter()
{
	// Hand over by creating a function list
	PACKET_ADAPTER *pa = NewPacketAdapter(HubPaInit,
		HubPaGetCancel, HubPaGetNextPacket, HubPaPutPacket, HubPaFree);

	return pa;
}