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
struct TYPE_4__ {int /*<<< orphan*/ * Sock; scalar_t__ Param; } ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  SESSION ;
typedef  TYPE_1__ RPC ;

/* Variables and functions */
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EndRpc (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseSession (int /*<<< orphan*/ *) ; 

void AdminDisconnect(RPC *rpc)
{
	SESSION *s;
	SOCK *sock;
	// Validate arguments
	if (rpc == NULL)
	{
		return;
	}

	s = (SESSION *)rpc->Param;
	sock = rpc->Sock;

	EndRpc(rpc);

	Disconnect(sock);
	ReleaseSession(s);
}