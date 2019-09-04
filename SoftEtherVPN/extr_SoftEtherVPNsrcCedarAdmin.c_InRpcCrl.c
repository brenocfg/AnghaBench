#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_12__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_11__ {void* Local; void* State; void* Country; void* Unit; void* Organization; void* CommonName; } ;
struct TYPE_10__ {TYPE_1__* Crl; int /*<<< orphan*/  Key; int /*<<< orphan*/  HubName; } ;
struct TYPE_9__ {int /*<<< orphan*/  DigestSHA1; int /*<<< orphan*/  DigestMD5; TYPE_3__* Name; int /*<<< orphan*/  Serial; } ;
typedef  TYPE_2__ RPC_CRL ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_3__ NAME ;
typedef  int /*<<< orphan*/  CRL ;
typedef  TYPE_4__ BUF ;

/* Variables and functions */
 void* CopyUniStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_4__*) ; 
 int MAX_SIZE ; 
 scalar_t__ MD5_SIZE ; 
 int /*<<< orphan*/  NewXSerial (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* PackGetBuf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ PackGetDataSize (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ PackGetUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ SHA1_SIZE ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 void* ZeroMalloc (int) ; 

void InRpcCrl(RPC_CRL *t, PACK *p)
{
	BUF *b;
	NAME *n;
	wchar_t tmp[MAX_SIZE];
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_CRL));
	PackGetStr(p, "HubName", t->HubName, sizeof(t->HubName));
	t->Key = PackGetInt(p, "Key");
	b = PackGetBuf(p, "Serial");
	t->Crl = ZeroMalloc(sizeof(CRL));
	if (b != NULL)
	{
		t->Crl->Serial = NewXSerial(b->Buf, b->Size);
		FreeBuf(b);
	}
	t->Crl->Name = ZeroMalloc(sizeof(NAME));
	n = t->Crl->Name;
	if (PackGetUniStr(p, "CommonName", tmp, sizeof(tmp)))
	{
		n->CommonName = CopyUniStr(tmp);
	}
	if (PackGetUniStr(p, "Organization", tmp, sizeof(tmp)))
	{
		n->Organization = CopyUniStr(tmp);
	}
	if (PackGetUniStr(p, "Unit", tmp, sizeof(tmp)))
	{
		n->Unit = CopyUniStr(tmp);
	}
	if (PackGetUniStr(p, "Country", tmp, sizeof(tmp)))
	{
		n->Country = CopyUniStr(tmp);
	}
	if (PackGetUniStr(p, "State", tmp, sizeof(tmp)))
	{
		n->State = CopyUniStr(tmp);
	}
	if (PackGetUniStr(p, "Local", tmp, sizeof(tmp)))
	{
		n->Local = CopyUniStr(tmp);
	}
	if (PackGetDataSize(p, "DigestMD5") == MD5_SIZE)
	{
		PackGetData(p, "DigestMD5", t->Crl->DigestMD5);
	}
	if (PackGetDataSize(p, "DigestSHA1") == SHA1_SIZE)
	{
		PackGetData(p, "DigestSHA1", t->Crl->DigestSHA1);
	}
}