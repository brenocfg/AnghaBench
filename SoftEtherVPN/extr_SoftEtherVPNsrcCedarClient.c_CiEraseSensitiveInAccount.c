#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_16__ {TYPE_1__* ClientAuth; } ;
struct TYPE_15__ {scalar_t__ AuthType; int /*<<< orphan*/  Username; int /*<<< orphan*/  PlainPassword; int /*<<< orphan*/  HashedPassword; } ;
typedef  TYPE_2__ RPC_CLIENT_CREATE_ACCOUNT ;
typedef  TYPE_3__ BUF ;

/* Variables and functions */
 scalar_t__ CLIENT_AUTHTYPE_PASSWORD ; 
 scalar_t__ CLIENT_AUTHTYPE_PLAIN_PASSWORD ; 
 TYPE_3__* CiAccountToCfg (TYPE_2__*) ; 
 TYPE_2__* CiCfgToAccount (TYPE_3__*) ; 
 int /*<<< orphan*/  CiFreeClientCreateAccount (TYPE_2__*) ; 
 int /*<<< orphan*/  ClearBuf (TYPE_3__*) ; 
 int /*<<< orphan*/  ClearStr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_3__*) ; 
 int /*<<< orphan*/  SeekBuf (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ ,int) ; 

bool CiEraseSensitiveInAccount(BUF *b)
{
	RPC_CLIENT_CREATE_ACCOUNT *a;
	BUF *b2;
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
		Zero(a->ClientAuth->HashedPassword, sizeof(a->ClientAuth->HashedPassword));
		ClearStr(a->ClientAuth->Username, sizeof(a->ClientAuth->Username));
	}
	else if (a->ClientAuth->AuthType == CLIENT_AUTHTYPE_PLAIN_PASSWORD)
	{
		ClearStr(a->ClientAuth->PlainPassword, sizeof(a->ClientAuth->PlainPassword));
		ClearStr(a->ClientAuth->Username, sizeof(a->ClientAuth->Username));
	}

	b2 = CiAccountToCfg(a);
	if (b2 != NULL)
	{
		ret = true;

		ClearBuf(b);

		WriteBuf(b, b2->Buf, b2->Size);
		SeekBuf(b, 0, 0);

		FreeBuf(b2);
	}

	CiFreeClientCreateAccount(a);
	Free(a);

	return ret;
}