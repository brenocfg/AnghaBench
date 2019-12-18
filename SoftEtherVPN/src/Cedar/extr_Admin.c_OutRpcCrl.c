#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * Local; int /*<<< orphan*/ * State; int /*<<< orphan*/ * Country; int /*<<< orphan*/ * Unit; int /*<<< orphan*/ * Organization; int /*<<< orphan*/ * CommonName; } ;
struct TYPE_8__ {TYPE_2__* Crl; int /*<<< orphan*/  Key; int /*<<< orphan*/  HubName; } ;
struct TYPE_7__ {int /*<<< orphan*/  DigestSHA1; int /*<<< orphan*/  DigestMD5; TYPE_4__* Name; TYPE_1__* Serial; } ;
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ RPC_CRL ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_4__ NAME ;

/* Variables and functions */
 int IsZero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MD5_SIZE ; 
 int /*<<< orphan*/  PackAddData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1_SIZE ; 

void OutRpcCrl(PACK *p, RPC_CRL *t)
{
	NAME *n;
	// Validate arguments
	if (p == NULL || t == NULL)
	{
		return;
	}

	PackAddStr(p, "HubName", t->HubName);
	PackAddInt(p, "Key", t->Key);

	if (t->Crl == NULL)
	{
		return;
	}

	if (t->Crl->Serial != NULL)
	{
		PackAddData(p, "Serial", t->Crl->Serial->data, t->Crl->Serial->size);
	}
	n = t->Crl->Name;
	if (n->CommonName != NULL)
	{
		PackAddUniStr(p, "CommonName", n->CommonName);
	}
	if (n->Organization != NULL)
	{
		PackAddUniStr(p, "Organization", n->Organization);
	}
	if (n->Unit != NULL)
	{
		PackAddUniStr(p, "Unit", n->Unit);
	}
	if (n->Country != NULL)
	{
		PackAddUniStr(p, "Country", n->Country);
	}
	if (n->State != NULL)
	{
		PackAddUniStr(p, "State", n->State);
	}
	if (n->Local != NULL)
	{
		PackAddUniStr(p, "Local", n->Local);
	}
	if (IsZero(t->Crl->DigestMD5, MD5_SIZE) == false)
	{
		PackAddData(p, "DigestMD5", t->Crl->DigestMD5, MD5_SIZE);
	}
	if (IsZero(t->Crl->DigestSHA1, SHA1_SIZE) == false)
	{
		PackAddData(p, "DigestSHA1", t->Crl->DigestSHA1, SHA1_SIZE);
	}
}