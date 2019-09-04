#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_14__ {int is_compatible_bit; int root_cert; } ;
struct TYPE_13__ {TYPE_1__* Server; } ;
struct TYPE_12__ {int Flag1; int /*<<< orphan*/ * Key; TYPE_6__* Cert; } ;
struct TYPE_11__ {int /*<<< orphan*/ * Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_KEY_PAIR ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_3__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_3__*,int /*<<< orphan*/ *,char*) ; 
 int CheckXandK (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int DownloadAndSaveIntermediateCertificatesIfNecessary (TYPE_6__*) ; 
 int /*<<< orphan*/  ERR_NOT_RSA_1024 ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  ERR_PROTOCOL_ERROR ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_1__*) ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 
 int /*<<< orphan*/  SetCedarCert (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ *) ; 

UINT StSetServerCert(ADMIN *a, RPC_KEY_PAIR *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;

	SERVER_ADMIN_ONLY;

	if (t->Cert == NULL || t->Key == NULL)
	{
		return ERR_PROTOCOL_ERROR;
	}

	if (t->Cert->is_compatible_bit == false)
	{
		return ERR_NOT_RSA_1024;
	}

	if (CheckXandK(t->Cert, t->Key) == false)
	{
		return ERR_PROTOCOL_ERROR;
	}

	t->Flag1 = 1;
	if (t->Cert->root_cert == false)
	{
		if (DownloadAndSaveIntermediateCertificatesIfNecessary(t->Cert) == false)
		{
			t->Flag1 = 0;
		}
	}

	SetCedarCert(c, t->Cert, t->Key);

	ALog(a, NULL, "LA_SET_SERVER_CERT");

	IncrementServerConfigRevision(s);

	return ERR_NO_ERROR;
}