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
 int /*<<< orphan*/  LinkPaFree ; 
 int /*<<< orphan*/  LinkPaGetCancel ; 
 int /*<<< orphan*/  LinkPaGetNextPacket ; 
 int /*<<< orphan*/  LinkPaInit ; 
 int /*<<< orphan*/  LinkPaPutPacket ; 
 int /*<<< orphan*/ * NewPacketAdapter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

PACKET_ADAPTER *LinkGetPacketAdapter()
{
	return NewPacketAdapter(LinkPaInit, LinkPaGetCancel, LinkPaGetNextPacket,
		LinkPaPutPacket, LinkPaFree);
}