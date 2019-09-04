#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ NumConnections; int /*<<< orphan*/  IpAddress; } ;
typedef  TYPE_1__ IP_CLIENT ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 TYPE_1__* SearchIpClient (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 TYPE_1__* ZeroMallocFast (int) ; 
 int /*<<< orphan*/  ip_clients ; 

void AddIpClient(IP *ip)
{
	IP_CLIENT *c;
	// Validate arguments
	if (ip == NULL)
	{
		return;
	}

	LockList(ip_clients);
	{
		c = SearchIpClient(ip);

		if (c == NULL)
		{
			c = ZeroMallocFast(sizeof(IP_CLIENT));
			Copy(&c->IpAddress, ip, sizeof(IP));
			c->NumConnections = 0;

			Add(ip_clients, c);
		}

		c->NumConnections++;
	}
	UnlockList(ip_clients);

	//Debug("AddIpClient: %r\n", ip);
}