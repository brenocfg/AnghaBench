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
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  SECURE_SIGN ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/ * CncConnect () ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcSecureSign (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcSecureSign (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  OutRpcSecureSign (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int PackGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * RecvPack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SendPack (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

bool CncSecureSignDlg(SECURE_SIGN *sign)
{
	SOCK *s;
	PACK *p;
	bool ret = false;
	// Validate arguments
	if (sign == NULL)
	{
		return false;
	}

	s = CncConnect();
	if (s == NULL)
	{
		return false;
	}

	p = NewPack();
	PackAddStr(p, "function", "secure_sign");
	OutRpcSecureSign(p, sign);

	SendPack(s, p);
	FreePack(p);

	p = RecvPack(s);
	if (p != NULL)
	{
		ret = PackGetBool(p, "ret");

		if (ret)
		{
			FreeRpcSecureSign(sign);

			Zero(sign, sizeof(SECURE_SIGN));
			InRpcSecureSign(sign, p);
		}

		FreePack(p);
	}

	Disconnect(s);
	ReleaseSock(s);

	return ret;
}