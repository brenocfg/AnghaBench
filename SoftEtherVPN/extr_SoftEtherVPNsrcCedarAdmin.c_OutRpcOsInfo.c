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
struct TYPE_3__ {int /*<<< orphan*/  KernelVersion; int /*<<< orphan*/  KernelName; int /*<<< orphan*/  OsVersion; int /*<<< orphan*/  OsVendorName; int /*<<< orphan*/  OsProductName; int /*<<< orphan*/  OsSystemName; int /*<<< orphan*/  OsServicePack; int /*<<< orphan*/  OsType; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ OS_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcOsInfo(PACK *p, OS_INFO *t)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddInt(p, "OsType", t->OsType);
	PackAddInt(p, "OsServicePack", t->OsServicePack);
	PackAddStr(p, "OsSystemName", t->OsSystemName);
	PackAddStr(p, "OsProductName", t->OsProductName);
	PackAddStr(p, "OsVendorName", t->OsVendorName);
	PackAddStr(p, "OsVersion", t->OsVersion);
	PackAddStr(p, "KernelName", t->KernelName);
	PackAddStr(p, "KernelVersion", t->KernelVersion);
}