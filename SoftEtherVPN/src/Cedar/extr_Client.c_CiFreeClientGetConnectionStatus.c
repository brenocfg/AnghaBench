#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * ClientX; int /*<<< orphan*/ * ServerX; } ;
typedef  TYPE_1__ RPC_CLIENT_GET_CONNECTION_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 

void CiFreeClientGetConnectionStatus(RPC_CLIENT_GET_CONNECTION_STATUS *st)
{
	// Validate arguments
	if (st == NULL)
	{
		return;
	}

	if (st->ServerX != NULL)
	{
		FreeX(st->ServerX);
	}

	if (st->ClientX != NULL)
	{
		FreeX(st->ClientX);
	}
}