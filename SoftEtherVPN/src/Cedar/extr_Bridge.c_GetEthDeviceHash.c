#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  size_t UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_10__ {size_t Num; TYPE_1__** Adapters; } ;
struct TYPE_9__ {size_t NumTokens; int /*<<< orphan*/ * Token; } ;
struct TYPE_8__ {int /*<<< orphan*/  Title; } ;
typedef  TYPE_2__ TOKEN_LIST ;
typedef  TYPE_3__ MS_ADAPTER_LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (size_t*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FreeToken (TYPE_2__*) ; 
 TYPE_2__* GetEthList () ; 
 TYPE_3__* MsCreateAdapterListEx (int) ; 
 int /*<<< orphan*/  MsFreeAdapterList (TYPE_3__*) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha0 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCat (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrLen (char*) ; 

UINT GetEthDeviceHash()
{
#ifdef	OS_UNIX
	// UNIX
	UINT num = 0;
	UINT i;
	char tmp[4096];
	UCHAR hash[SHA1_SIZE];
	TOKEN_LIST *t = GetEthList();

	tmp[0] = 0;

	if (t != NULL)
	{
		num = t->NumTokens;
		for (i = 0; i < t->NumTokens; i++)
		{
			StrCat(tmp, sizeof(tmp), t->Token[i]);
		}
		FreeToken(t);
	}

	Sha0(hash, tmp, StrLen(tmp));

	Copy(&num, hash, sizeof(UINT));

	return num;
#else	// OS_UNIX
	// Win32
	UINT ret = 0;
	MS_ADAPTER_LIST *a = MsCreateAdapterListEx(true);
	UINT num;
	UINT i;
	char tmp[4096];
	UCHAR hash[SHA1_SIZE];

	tmp[0] = 0;
	if (a != NULL)
	{
		for (i = 0;i < a->Num;i++)
		{
			StrCat(tmp, sizeof(tmp), a->Adapters[i]->Title);
		}
	}
	MsFreeAdapterList(a);

	Sha0(hash, tmp, StrLen(tmp));

	Copy(&num, hash, sizeof(UINT));

	return num;
#endif	// OS_UNIX
}