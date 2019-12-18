#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_15__ {int /*<<< orphan*/ * MacAddress; int /*<<< orphan*/  Name; int /*<<< orphan*/  Enabled; } ;
typedef  TYPE_2__ UNIX_VLAN ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_18__ {int Size; int /*<<< orphan*/ * Buf; } ;
struct TYPE_14__ {int /*<<< orphan*/  NicDownOnDisconnect; } ;
struct TYPE_17__ {TYPE_1__ Config; int /*<<< orphan*/  UnixVLanList; } ;
struct TYPE_16__ {int /*<<< orphan*/  Name; } ;
typedef  TYPE_3__ FOLDER ;
typedef  TYPE_4__ CLIENT ;
typedef  TYPE_5__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  CfgGetBool (TYPE_3__*,char*) ; 
 int CfgGetStr (TYPE_3__*,char*,char*,int) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_5__*) ; 
 scalar_t__ IsZero (int /*<<< orphan*/ *,int) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_5__* StrToBin (char*) ; 
 int /*<<< orphan*/  UnixVLanCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* ZeroMalloc (int) ; 

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