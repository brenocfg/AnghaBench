#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_13__ {int /*<<< orphan*/  Enabled; int /*<<< orphan*/  Name; int /*<<< orphan*/ * MacAddress; } ;
typedef  TYPE_1__ UNIX_VLAN ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_16__ {int Size; int /*<<< orphan*/ * Buf; } ;
struct TYPE_15__ {int /*<<< orphan*/  UnixVLanList; } ;
struct TYPE_14__ {int /*<<< orphan*/  Name; } ;
typedef  TYPE_2__ FOLDER ;
typedef  TYPE_3__ CLIENT ;
typedef  TYPE_4__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  CfgGetBool (TYPE_2__*,char*) ; 
 int CfgGetStr (TYPE_2__*,char*,char*,int) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_4__*) ; 
 scalar_t__ IsZero (int /*<<< orphan*/ *,int) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* StrToBin (char*) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void CiLoadVLan(CLIENT *c, FOLDER *f)
{
	char tmp[MAX_SIZE];
	UCHAR addr[6];
	BUF *b;
	UNIX_VLAN *v;
	// Validate arguments
	if (c == NULL || f == NULL)
	{
		return;
	}

	if (CfgGetStr(f, "MacAddress", tmp, sizeof(tmp)) == false)
	{
		return;
	}

	b = StrToBin(tmp);
	if (b == NULL)
	{
		return;
	}

	if (b->Size != 6)
	{
		FreeBuf(b);
		return;
	}

	Copy(addr, b->Buf, 6);

	FreeBuf(b);

	if (IsZero(addr, 6))
	{
		return;
	}

	v = ZeroMalloc(sizeof(UNIX_VLAN));
	Copy(v->MacAddress, addr, 6);
	StrCpy(v->Name, sizeof(v->Name), f->Name);
	v->Enabled = CfgGetBool(f, "Enabled");

	Add(c->UnixVLanList, v);

#ifdef	OS_UNIX
	UnixVLanCreate(v->Name, v->MacAddress, !c->Config.NicDownOnDisconnect);
#endif	// OS_UNIX
}