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
typedef  int /*<<< orphan*/  sign ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  SECURE_SIGN ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcSecureSign (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcSecureSign (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  OutRpcSecureSign (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  SendPack (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int Win32CiSecureSign (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

void CnSecureSign(SOCK *s, PACK *p)
{
	SECURE_SIGN sign;
	bool ret = false;
	// Validate arguments
	if (s == NULL || p == NULL)
	{
		return;
	}

	Zero(&sign, sizeof(sign));
	InRpcSecureSign(&sign, p);

#ifdef	OS_WIN32
	// Win32: Show dialog
	ret = Win32CiSecureSign(&sign);
#else	// OS_WIN32
	// UNIX: not implemented
	ret = false;
#endif	// OS_WIN32

	p = NewPack();

	OutRpcSecureSign(p, &sign);
	FreeRpcSecureSign(&sign);

	PackAddBool(p, "ret", ret);

	SendPack(s, p);
	FreePack(p);
}