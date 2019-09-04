#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* ClientAuth; } ;
struct TYPE_6__ {scalar_t__ AuthType; } ;
typedef  TYPE_2__ RPC_CLIENT_CREATE_ACCOUNT ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 scalar_t__ CLIENT_AUTHTYPE_PASSWORD ; 
 scalar_t__ CLIENT_AUTHTYPE_PLAIN_PASSWORD ; 
 TYPE_2__* CiCfgToAccount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiFreeClientCreateAccount (TYPE_2__*) ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 

bool CiHasAccountSensitiveInformation(BUF *b)
{
	RPC_CLIENT_CREATE_ACCOUNT *a;
	bool ret = false;
	// Validate arguments
	if (b == NULL)
	{
		return false;
	}

	a = CiCfgToAccount(b);
	if (a == NULL)
	{
		return false;
	}

	if (a->ClientAuth->AuthType == CLIENT_AUTHTYPE_PASSWORD)
	{
		ret = true;
	}
	else if (a->ClientAuth->AuthType == CLIENT_AUTHTYPE_PLAIN_PASSWORD)
	{
		ret = true;
	}

	CiFreeClientCreateAccount(a);
	Free(a);

	return ret;
}