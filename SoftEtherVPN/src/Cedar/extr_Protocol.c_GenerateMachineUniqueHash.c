#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  UINT64 ;
struct TYPE_9__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_8__ {char OsType; char* KernelName; char* KernelVersion; char* OsProductName; char OsServicePack; char* OsSystemName; char* OsVendorName; char* OsVersion; } ;
typedef  TYPE_1__ OS_INFO ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 int /*<<< orphan*/  GetHostIPAddressListHash () ; 
 int /*<<< orphan*/  GetMachineName (char*,int) ; 
 TYPE_1__* GetOsInfo () ; 
 TYPE_2__* NewBuf () ; 
 int /*<<< orphan*/  Sha0 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int StrLen (char*) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  WriteBufInt64 (TYPE_2__*,int /*<<< orphan*/ ) ; 

void GenerateMachineUniqueHash(void *data)
{
	BUF *b;
	char name[64];
	OS_INFO *osinfo;
	UINT64 iphash = 0;
	// Validate arguments
	if (data == NULL)
	{
		return;
	}

	iphash = GetHostIPAddressListHash();

	b = NewBuf();
	GetMachineName(name, sizeof(name));

	osinfo = GetOsInfo();

	WriteBuf(b, name, StrLen(name));

	WriteBufInt64(b, iphash);

	WriteBuf(b, &osinfo->OsType, sizeof(osinfo->OsType));
	WriteBuf(b, osinfo->KernelName, StrLen(osinfo->KernelName));
	WriteBuf(b, osinfo->KernelVersion, StrLen(osinfo->KernelVersion));
	WriteBuf(b, osinfo->OsProductName, StrLen(osinfo->OsProductName));
	WriteBuf(b, &osinfo->OsServicePack, sizeof(osinfo->OsServicePack));
	WriteBuf(b, osinfo->OsSystemName, StrLen(osinfo->OsSystemName));
	WriteBuf(b, osinfo->OsVendorName, StrLen(osinfo->OsVendorName));
	WriteBuf(b, osinfo->OsVersion, StrLen(osinfo->OsVersion));

	Sha0(data, b->Buf, b->Size);

	FreeBuf(b);
}