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
typedef  int /*<<< orphan*/  machine_name ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 int /*<<< orphan*/  GetMachineHostName (char*,int) ; 
 int MAX_SIZE ; 
 TYPE_1__* NewBuf () ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrUpper (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WriteBufStr (TYPE_1__*,char*) ; 

void NsGenMacAddressSignatureForMachine(UCHAR *dst_last_2, UCHAR *src_mac_addr_4)
{
	char machine_name[MAX_SIZE];
	BUF *b;
	UCHAR hash[SHA1_SIZE];
	// Validate arguments
	if (dst_last_2 == NULL || src_mac_addr_4 == NULL)
	{
		return;
	}

	GetMachineHostName(machine_name, sizeof(machine_name));

	Trim(machine_name);
	StrUpper(machine_name);

	b = NewBuf();
	WriteBuf(b, src_mac_addr_4, 4);
	WriteBufStr(b, machine_name);

	Sha1(hash, b->Buf, b->Size);

	FreeBuf(b);

	Copy(dst_last_2, hash, 2);
}