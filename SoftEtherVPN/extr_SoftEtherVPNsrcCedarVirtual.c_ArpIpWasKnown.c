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
typedef  int /*<<< orphan*/  VH ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteArpWaitTable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InsertArpTable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendWaitingIp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ArpIpWasKnown(VH *v, UINT ip, UCHAR *mac)
{
	// Validate arguments
	if (v == NULL || mac == NULL)
	{
		return;
	}

	// If there is a query for this IP address in the ARP queue, delete it
	DeleteArpWaitTable(v, ip);

	// Update or register in the ARP table
	InsertArpTable(v, mac, ip);

	// Send the IP packets waiting in the IP waiting list
	SendWaitingIp(v, mac, ip);
}