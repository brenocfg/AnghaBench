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
 int /*<<< orphan*/ * NewPacketAdapter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NullPaFree ; 
 int /*<<< orphan*/  NullPaGetCancel ; 
 int /*<<< orphan*/  NullPaGetNextPacket ; 
 int /*<<< orphan*/  NullPaInit ; 
 int /*<<< orphan*/  NullPaPutPacket ; 

PACKET_ADAPTER *NullGetPacketAdapter()
{
	PACKET_ADAPTER *pa = NewPacketAdapter(NullPaInit, NullPaGetCancel, NullPaGetNextPacket,
		NullPaPutPacket, NullPaFree);

	return pa;
}