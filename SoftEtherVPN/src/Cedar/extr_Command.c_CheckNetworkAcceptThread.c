#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_2__ {int /*<<< orphan*/  k; int /*<<< orphan*/  x; int /*<<< orphan*/ * s; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  TYPE_1__ CHECK_NETWORK_2 ;

/* Variables and functions */
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 
 scalar_t__ Send (int /*<<< orphan*/ *,scalar_t__*,int,int) ; 
 scalar_t__ StartSSL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void CheckNetworkAcceptThread(THREAD *thread, void *param)
{
	CHECK_NETWORK_2 *c = (CHECK_NETWORK_2 *)param;
	SOCK *s = c->s;
	UINT i = 0;

	if (StartSSL(s, c->x, c->k))
	{
		while (true)
		{
			i++;
			if (Send(s, &i, sizeof(UINT), true) == 0)
			{
				break;
			}
		}
	}

	Disconnect(s);
	ReleaseSock(s);
}