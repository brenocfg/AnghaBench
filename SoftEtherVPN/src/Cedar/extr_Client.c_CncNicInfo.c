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
struct TYPE_3__ {char* NicName; int /*<<< orphan*/  AccountName; } ;
typedef  TYPE_1__ UI_NICINFO ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/ * CncConnectEx (int) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  PackAddUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendPack (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

SOCK *CncNicInfo(UI_NICINFO *info)
{
	SOCK *s;
	PACK *p;
	// Validate arguments
	if (info == NULL)
	{
		return NULL;
	}

	s = CncConnectEx(200);
	if (s == NULL)
	{
		return NULL;
	}

	p = NewPack();
	PackAddStr(p, "function", "nicinfo");
	PackAddStr(p, "NicName", info->NicName);
	PackAddUniStr(p, "AccountName", info->AccountName);

	SendPack(s, p);
	FreePack(p);

	return s;
}