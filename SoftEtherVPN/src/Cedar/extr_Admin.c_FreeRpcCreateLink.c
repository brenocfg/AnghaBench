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
struct TYPE_3__ {int /*<<< orphan*/  ClientAuth; int /*<<< orphan*/  ClientOption; int /*<<< orphan*/ * ServerCert; } ;
typedef  TYPE_1__ RPC_CREATE_LINK ;

/* Variables and functions */
 int /*<<< orphan*/  CiFreeClientAuth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 

void FreeRpcCreateLink(RPC_CREATE_LINK *t)
{
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	if (t->ServerCert != NULL)
	{
		FreeX(t->ServerCert);
	}
	Free(t->ClientOption);
	CiFreeClientAuth(t->ClientAuth);
}