#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  machine_name ;
typedef  int /*<<< orphan*/  exe_path ;
typedef  scalar_t__ UINT ;
struct TYPE_5__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  char IP ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeHostIPAddressList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetExeNameW (char*,int) ; 
 int /*<<< orphan*/ * GetHostIPAddressList () ; 
 int /*<<< orphan*/  GetMachineHostName (char*,int) ; 
 char* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int MAX_SIZE ; 
 char* MsRegReadStr (int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_1__* NewBuf () ; 
 int /*<<< orphan*/  REG_LOCAL_MACHINE ; 
 int /*<<< orphan*/  Sha1 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int StrSize (char*) ; 
 int /*<<< orphan*/  StrUpper (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int UniStrSize (char*) ; 
 int /*<<< orphan*/  UniStrUpper (char*) ; 
 int /*<<< orphan*/  UniTrim (char*) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_1__*,char*,int) ; 

void GetCurrentMachineIpProcessHashInternal(void *hash)
{
	BUF *b;
	LIST *ip_list;
	char machine_name[MAX_SIZE];
	wchar_t exe_path[MAX_PATH];
	char *product_id = NULL;
	// Validate arguments
	if (hash == NULL)
	{
		return;
	}

#ifdef	OS_WIN32
	product_id = MsRegReadStr(REG_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "ProductId");
	if (product_id == NULL)
	{
		product_id = MsRegReadStr(REG_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion", "ProductId");
	}
#endif	// OS_WIN32

	b = NewBuf();

	GetMachineHostName(machine_name, sizeof(machine_name));
	Trim(machine_name);
	StrUpper(machine_name);

	GetExeNameW(exe_path, sizeof(exe_path));
	UniTrim(exe_path);
	UniStrUpper(exe_path);

	WriteBuf(b, machine_name, StrSize(machine_name));
	WriteBuf(b, exe_path, UniStrSize(exe_path));
	WriteBuf(b, product_id, StrSize(product_id));

	ip_list = GetHostIPAddressList();
	if (ip_list != NULL)
	{
		UINT i;
		for (i = 0;i < LIST_NUM(ip_list);i++)
		{
			IP *ip = LIST_DATA(ip_list, i);

			WriteBuf(b, ip, sizeof(IP));
		}
	}
	FreeHostIPAddressList(ip_list);

	Sha1(hash, b->Buf, b->Size);

	FreeBuf(b);

	Free(product_id);
}