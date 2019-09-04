#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  u ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  st ;
typedef  int /*<<< orphan*/  org ;
typedef  int /*<<< orphan*/  l ;
typedef  int /*<<< orphan*/  cn ;
typedef  int /*<<< orphan*/  c ;
typedef  size_t UINT ;
struct TYPE_12__ {int Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_11__ {int /*<<< orphan*/  DigestSHA1; int /*<<< orphan*/  DigestMD5; int /*<<< orphan*/  Serial; int /*<<< orphan*/  Name; } ;
struct TYPE_10__ {size_t NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_2__ CRL ;
typedef  TYPE_3__ BUF ;

/* Variables and functions */
 TYPE_1__* CfgEnumFolderToTokenList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CfgGetFolder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ CfgGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  CfgGetUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_3__*) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 scalar_t__ MD5_SIZE ; 
 int /*<<< orphan*/  NewName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NewXSerial (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SHA1_SIZE ; 
 TYPE_3__* StrToBin (char*) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ *) ; 
 TYPE_2__* ZeroMalloc (int) ; 

void SiLoadCrlList(LIST *o, FOLDER *f)
{
	// Validate arguments
	if (o == NULL || f == NULL)
	{
		return;
	}

	LockList(o);
	{
		UINT i;
		TOKEN_LIST *t;

		t = CfgEnumFolderToTokenList(f);

		for (i = 0;i < t->NumTokens;i++)
		{
			CRL *crl;
			FOLDER *ff = CfgGetFolder(f, t->Token[i]);
			wchar_t cn[MAX_SIZE], org[MAX_SIZE], u[MAX_SIZE], c[MAX_SIZE],
				st[MAX_SIZE], l[MAX_SIZE];
			char tmp[MAX_SIZE];

			if (ff != NULL)
			{
				BUF *b;

				crl = ZeroMalloc(sizeof(CRL));

				CfgGetUniStr(ff, "CommonName", cn, sizeof(cn));
				CfgGetUniStr(ff, "Organization", org, sizeof(org));
				CfgGetUniStr(ff, "Unit", u, sizeof(u));
				CfgGetUniStr(ff, "Country", c, sizeof(c));
				CfgGetUniStr(ff, "State", st, sizeof(st));
				CfgGetUniStr(ff, "Local", l, sizeof(l));

				crl->Name = NewName(cn, org, u, c, st, l);

				if (CfgGetStr(ff, "Serial", tmp, sizeof(tmp)))
				{
					b = StrToBin(tmp);

					if (b != NULL)
					{
						if (b->Size >= 1)
						{
							crl->Serial = NewXSerial(b->Buf, b->Size);
						}

						FreeBuf(b);
					}
				}

				if (CfgGetStr(ff, "DigestMD5", tmp, sizeof(tmp)))
				{
					b = StrToBin(tmp);

					if (b != NULL)
					{
						if (b->Size == MD5_SIZE)
						{
							Copy(crl->DigestMD5, b->Buf, MD5_SIZE);
						}

						FreeBuf(b);
					}
				}

				if (CfgGetStr(ff, "DigestSHA1", tmp, sizeof(tmp)))
				{
					b = StrToBin(tmp);

					if (b != NULL)
					{
						if (b->Size == SHA1_SIZE)
						{
							Copy(crl->DigestSHA1, b->Buf, SHA1_SIZE);
						}

						FreeBuf(b);
					}
				}

				Insert(o, crl);
			}
		}

		FreeToken(t);
	}
	UnlockList(o);
}