#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  name ;
typedef  scalar_t__ UINT ;
struct TYPE_7__ {TYPE_1__* Serial; int /*<<< orphan*/  DigestSHA1; int /*<<< orphan*/  DigestMD5; TYPE_2__* Name; } ;
struct TYPE_6__ {int /*<<< orphan*/  Local; int /*<<< orphan*/  State; int /*<<< orphan*/  Country; int /*<<< orphan*/  Unit; int /*<<< orphan*/  Organization; int /*<<< orphan*/  CommonName; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ NAME ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_3__ CRL ;

/* Variables and functions */
 int /*<<< orphan*/  BinToStr (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  CfgAddUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CfgCreateFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Format (char*,int,char*,scalar_t__) ; 
 int IsZero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MD5_SIZE ; 
 int /*<<< orphan*/  SHA1_SIZE ; 
 int UniIsEmptyStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ *) ; 

void SiWriteCrlList(FOLDER *f, LIST *o)
{
	// Validate arguments
	if (f == NULL || o == NULL)
	{
		return;
	}

	LockList(o);
	{
		UINT i;
		for (i = 0;i < LIST_NUM(o);i++)
		{
			char name[MAX_SIZE];
			CRL *crl = LIST_DATA(o, i);
			FOLDER *ff;
			NAME *n;

			Format(name, sizeof(name), "Crl%u", i);

			ff = CfgCreateFolder(f, name);
			n = crl->Name;

			if (UniIsEmptyStr(n->CommonName) == false)
			{
				CfgAddUniStr(ff, "CommonName", n->CommonName);
			}

			if (UniIsEmptyStr(n->Organization) == false)
			{
				CfgAddUniStr(ff, "Organization", n->Organization);
			}

			if (UniIsEmptyStr(n->Unit) == false)
			{
				CfgAddUniStr(ff, "Unit", n->Unit);
			}

			if (UniIsEmptyStr(n->Country) == false)
			{
				CfgAddUniStr(ff, "Country", n->Country);
			}

			if (UniIsEmptyStr(n->State) == false)
			{
				CfgAddUniStr(ff, "State", n->State);
			}

			if (UniIsEmptyStr(n->Local) == false)
			{
				CfgAddUniStr(ff, "Local", n->Local);
			}

			if (IsZero(crl->DigestMD5, MD5_SIZE) == false)
			{
				char tmp[MAX_SIZE];

				BinToStr(tmp, sizeof(tmp), crl->DigestMD5, MD5_SIZE);
				CfgAddStr(ff, "DigestMD5", tmp);
			}

			if (IsZero(crl->DigestSHA1, SHA1_SIZE) == false)
			{
				char tmp[MAX_SIZE];

				BinToStr(tmp, sizeof(tmp), crl->DigestSHA1, SHA1_SIZE);
				CfgAddStr(ff, "DigestSHA1", tmp);
			}

			if (crl->Serial != NULL)
			{
				char tmp[MAX_SIZE];

				BinToStr(tmp, sizeof(tmp), crl->Serial->data, crl->Serial->size);
				CfgAddStr(ff, "Serial", tmp);
			}
		}
	}
	UnlockList(o);
}