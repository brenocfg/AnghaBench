#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  machine_name ;
typedef  int /*<<< orphan*/  hash ;
typedef  int /*<<< orphan*/  exe_path ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 int /*<<< orphan*/  GetExeNameW (char*,int) ; 
 int /*<<< orphan*/  GetMachineHostName (char*,int) ; 
 int MAX_PATH ; 
 int MAX_SIZE ; 
 char* MsRegReadStr (int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_1__* NewBuf () ; 
 int /*<<< orphan*/ * NewUDPEx2Rand (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_LOCAL_MACHINE ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrSize (char*) ; 
 int /*<<< orphan*/  StrUpper (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int /*<<< orphan*/  UniStrSize (char*) ; 
 int /*<<< orphan*/  UniStrUpper (char*) ; 
 int /*<<< orphan*/  UniTrim (char*) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBufChar (TYPE_1__*,int /*<<< orphan*/ ) ; 

SOCK *NewUDPEx2RandMachineAndExePath(bool ipv6, IP *ip, UINT num_retry, UCHAR rand_port_id)
{
	BUF *b;
	char machine_name[MAX_SIZE];
	wchar_t exe_path[MAX_PATH];
	char *product_id = NULL;
	UCHAR hash[SHA1_SIZE];

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
	WriteBufChar(b, rand_port_id);
	//WriteBufInt(b, GetHostIPAddressHash32());

	Sha1(hash, b->Buf, b->Size);

	FreeBuf(b);

	Free(product_id);

	return NewUDPEx2Rand(ipv6, ip, hash, sizeof(hash), num_retry);
}