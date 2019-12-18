#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  OsProductName; } ;
struct TYPE_6__ {int /*<<< orphan*/  Title; } ;
typedef  TYPE_1__ RPC_WINVER ;

/* Variables and functions */
 TYPE_5__* GetOsInfo () ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Win32GetWinVer (TYPE_1__*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void GetWinVer(RPC_WINVER *v)
{
	// Validate arguments
	if (v == NULL)
	{
		return;
	}

#ifdef	OS_WIN32
	Win32GetWinVer(v);
#else	// OS_WIN32
	Zero(v, sizeof(RPC_WINVER));
	StrCpy(v->Title, sizeof(v->Title), GetOsInfo()->OsProductName);
#endif	// OS_WIN32
}