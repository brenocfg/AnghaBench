#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_10__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_9__ {int* MacAddress; int /*<<< orphan*/  IpAddress; int /*<<< orphan*/ * HubName; TYPE_1__* Switch; } ;
struct TYPE_8__ {int /*<<< orphan*/ * Name; } ;
typedef  TYPE_2__ L3IF ;
typedef  TYPE_3__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_3__*) ; 
 int /*<<< orphan*/  GenMacAddress (int*) ; 
 TYPE_3__* NewBuf () ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int StrLen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_3__*,int /*<<< orphan*/ *,int) ; 

void L3GenerateMacAddress(L3IF *f)
{
	BUF *b;
	UCHAR hash[SHA1_SIZE];
	// Validate arguments
	if (f == NULL)
	{
		return;
	}

	b = NewBuf();
	WriteBuf(b, f->Switch->Name, StrLen(f->Switch->Name));
	WriteBuf(b, f->HubName, StrLen(f->HubName));
	WriteBuf(b, &f->IpAddress, sizeof(f->IpAddress));

	GenMacAddress(f->MacAddress);
	Sha0(hash, b->Buf, b->Size);
	Copy(f->MacAddress + 2, hash, 4);
	f->MacAddress[1] = 0xA3;
	FreeBuf(b);
}