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
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int UCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int*,int*,int) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 int /*<<< orphan*/  GetMachineHostName (char*,int) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MsGetCurrentProcessId () ; 
 TYPE_1__* NewBuf () ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha1 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBufInt (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBufStr (TYPE_1__*,char*) ; 

void NullGenerateMacAddress(UCHAR *mac, UINT id, UINT seq)
{
	UCHAR hash[SHA1_SIZE];
	char name[MAX_SIZE];
	BUF *b;
	// Validate arguments
	if (mac == NULL)
	{
		return;
	}

	b = NewBuf();
	WriteBufInt(b, id);
	WriteBufInt(b, seq);
	GetMachineHostName(name, sizeof(name));
#ifdef	OS_WIN32
	WriteBufInt(b, MsGetCurrentProcessId());
#endif	// OS_WIN32
	WriteBufStr(b, name);

	Sha1(hash, b->Buf, b->Size);

	FreeBuf(b);

	Copy(mac, hash, 6);
	mac[0] = 0x7E;
}