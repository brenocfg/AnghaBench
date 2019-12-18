#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  size_t UINT ;
struct TYPE_12__ {int NumItem; TYPE_2__* Items; } ;
struct TYPE_11__ {char* DeviceName; int /*<<< orphan*/  NetworkConnectionName; } ;
struct TYPE_10__ {int NumTokens; char** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  TYPE_2__ RPC_ENUM_ETH_ITEM ;
typedef  TYPE_3__ RPC_ENUM_ETH ;
typedef  int /*<<< orphan*/  ADMIN ;

/* Variables and functions */
 size_t ERR_NOT_SUPPORTED ; 
 size_t ERR_NO_ERROR ; 
 int EthGetInterfaceDescriptionUnix (char*,char*,int) ; 
 int EthIsInterfaceDescriptionSupportedUnix () ; 
 int /*<<< orphan*/  FreeRpcEnumEth (TYPE_3__*) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 TYPE_1__* GetEthList () ; 
 int /*<<< orphan*/  GetEthNetworkConnectionName (int /*<<< orphan*/ ,int,char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 
 TYPE_2__* ZeroMalloc (int) ; 

UINT StEnumEthernet(ADMIN *a, RPC_ENUM_ETH *t)
{
	TOKEN_LIST *o;
	UINT i;
	char tmp[MAX_SIZE];
	bool unix_support = false;

	SERVER_ADMIN_ONLY;

#ifdef	OS_UNIX
	unix_support = EthIsInterfaceDescriptionSupportedUnix();
#endif	// OS_UNIX

	o = GetEthList();
	if (o == NULL)
	{
		return ERR_NOT_SUPPORTED;
	}

	FreeRpcEnumEth(t);
	Zero(t, sizeof(RPC_ENUM_ETH));

	t->NumItem = o->NumTokens;
	t->Items = ZeroMalloc(sizeof(RPC_ENUM_ETH_ITEM) * t->NumItem);

	for (i = 0;i < t->NumItem;i++)
	{
		RPC_ENUM_ETH_ITEM *e = &t->Items[i];

		StrCpy(e->DeviceName, sizeof(e->DeviceName), o->Token[i]);

		StrCpy(tmp, sizeof(tmp), e->DeviceName);

#ifdef OS_WIN32
		GetEthNetworkConnectionName(e->NetworkConnectionName, sizeof(e->NetworkConnectionName), e->DeviceName);
#else
		if (unix_support == false)
		{
			StrCpy(tmp, sizeof(tmp), "");
		}
		else
		{
			if (EthGetInterfaceDescriptionUnix(e->DeviceName, tmp, sizeof(tmp)) == false)
			{
				StrCpy(tmp, sizeof(tmp), e->DeviceName);
			}
		}

		StrToUni(e->NetworkConnectionName, sizeof(e->NetworkConnectionName), tmp);
#endif
	}

	FreeToken(o);

	return ERR_NO_ERROR;
}