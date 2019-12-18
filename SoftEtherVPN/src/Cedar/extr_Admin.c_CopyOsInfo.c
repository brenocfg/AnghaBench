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
struct TYPE_4__ {void* KernelVersion; void* KernelName; void* OsVersion; void* OsVendorName; void* OsProductName; void* OsSystemName; int /*<<< orphan*/  OsServicePack; int /*<<< orphan*/  OsType; } ;
typedef  TYPE_1__ OS_INFO ;

/* Variables and functions */
 void* CopyStr (void*) ; 

void CopyOsInfo(OS_INFO *dst, OS_INFO *info)
{
	// Validate arguments
	if (info == NULL || dst == NULL)
	{
		return;
	}

	dst->OsType = info->OsType;
	dst->OsServicePack = info->OsServicePack;
	dst->OsSystemName = CopyStr(info->OsSystemName);
	dst->OsProductName = CopyStr(info->OsProductName);
	dst->OsVendorName = CopyStr(info->OsVendorName);
	dst->OsVersion = CopyStr(info->OsVersion);
	dst->KernelName = CopyStr(info->KernelName);
	dst->KernelVersion = CopyStr(info->KernelVersion);
}