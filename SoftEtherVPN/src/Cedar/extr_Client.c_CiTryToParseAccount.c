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
typedef  int /*<<< orphan*/  RPC_CLIENT_CREATE_ACCOUNT ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * CiCfgToAccount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiFreeClientCreateAccount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 

bool CiTryToParseAccount(BUF *b)
{
	RPC_CLIENT_CREATE_ACCOUNT *a;
	// Validate arguments
	if (b == NULL)
	{
		return false;
	}

	a = CiCfgToAccount(b);
	if (a != NULL)
	{
		CiFreeClientCreateAccount(a);
		Free(a);

		return true;
	}
	else
	{
		return false;
	}
}