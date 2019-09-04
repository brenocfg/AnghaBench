#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_4__ {void* KernelVersion; void* KernelName; void* OsVersion; void* OsVendorName; void* OsProductName; void* OsSystemName; void* OsServicePack; void* OsType; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ OS_INFO ;

/* Variables and functions */
 void* CopyStr (char*) ; 
 int MAX_SIZE ; 
 void* PackGetInt (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ PackGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcOsInfo(OS_INFO *t, PACK *p)
{
	char tmp[MAX_SIZE];
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(OS_INFO));
	t->OsType = PackGetInt(p, "OsType");
	t->OsServicePack = PackGetInt(p, "OsServicePack");
	if (PackGetStr(p, "OsSystemName", tmp, sizeof(tmp)))
	{
		t->OsSystemName = CopyStr(tmp);
	}
	if (PackGetStr(p, "OsProductName", tmp, sizeof(tmp)))
	{
		t->OsProductName = CopyStr(tmp);
	}
	if (PackGetStr(p, "OsVendorName", tmp, sizeof(tmp)))
	{
		t->OsVendorName = CopyStr(tmp);
	}
	if (PackGetStr(p, "OsVersion", tmp, sizeof(tmp)))
	{
		t->OsVersion = CopyStr(tmp);
	}
	if (PackGetStr(p, "KernelName", tmp, sizeof(tmp)))
	{
		t->KernelName = CopyStr(tmp);
	}
	if (PackGetStr(p, "KernelVersion", tmp, sizeof(tmp)))
	{
		t->KernelVersion = CopyStr(tmp);
	}
}