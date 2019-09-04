#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_12__ {int IpAddress; scalar_t__ Expire; int /*<<< orphan*/  MacAddress; } ;
struct TYPE_11__ {int /*<<< orphan*/  ArpTable; } ;
typedef  TYPE_1__ L3IF ;
typedef  TYPE_2__ L3ARPENTRY ;

/* Variables and functions */
 scalar_t__ ARP_ENTRY_EXPIRES ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  L3SendWaitingIp (TYPE_1__*,int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 TYPE_2__* Search (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 TYPE_2__* ZeroMalloc (int) ; 

void L3InsertArpTable(L3IF *f, UINT ip, UCHAR *mac)
{
	L3ARPENTRY *a, t;
	// Validate arguments
	if (f == NULL || ip == 0 || ip == 0xffffffff || mac == NULL)
	{
		return;
	}

	Zero(&t, sizeof(t));
	t.IpAddress = ip;

	a = Search(f->ArpTable, &t);

	if (a == NULL)
	{
		// Since this is not registered, register this
		a = ZeroMalloc(sizeof(L3ARPENTRY));
		a->IpAddress = ip;
		Copy(a->MacAddress, mac, 6);
		Insert(f->ArpTable, a);
	}

	// Extend the expiration date
	a->Expire = Tick64() + ARP_ENTRY_EXPIRES;

	// Send waiting IP packets
	L3SendWaitingIp(f, mac, ip, a);
}