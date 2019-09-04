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
struct TYPE_5__ {scalar_t__ NumConnections; } ;
typedef  TYPE_1__ IP_CLIENT ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 TYPE_1__* SearchIpClient (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_clients ; 

void DelIpClient(IP *ip)
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

		if (c != NULL)
		{
			c->NumConnections--;

			if (c->NumConnections == 0)
			{
				Delete(ip_clients, c);
				Free(c);
			}
		}
	}
	UnlockList(ip_clients);

	//Debug("DelIpClient: %r\n", ip);
}