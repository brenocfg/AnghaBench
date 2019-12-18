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
struct TYPE_3__ {int /*<<< orphan*/  ClientOption; int /*<<< orphan*/  ClientAuth; int /*<<< orphan*/ * ServerCert; } ;
typedef  TYPE_1__ RPC_CLIENT_GET_ACCOUNT ;

/* Variables and functions */
 int /*<<< orphan*/  CiFreeClientAuth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 

void CiFreeClientGetAccount(RPC_CLIENT_GET_ACCOUNT *a)
{
	// Validate arguments
	if (a == NULL)
	{
		return;
	}

	// Release the account information
	if (a->ServerCert != NULL)
	{
		FreeX(a->ServerCert);
	}
	CiFreeClientAuth(a->ClientAuth);
	Free(a->ClientOption);
}