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
typedef  int /*<<< orphan*/  X ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_10__ {TYPE_1__* Server; } ;
struct TYPE_9__ {int /*<<< orphan*/  StrValue; } ;
struct TYPE_8__ {int /*<<< orphan*/ * Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_TEST ;
typedef  int /*<<< orphan*/  K ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_3__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_3__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_1__*) ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 
 int /*<<< orphan*/  SetCedarCert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiGenerateDefaultCertEx (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

UINT StRegenerateServerCert(ADMIN *a, RPC_TEST *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	UINT ret = ERR_NO_ERROR;
	X *x;
	K *k;

	SERVER_ADMIN_ONLY;

	SiGenerateDefaultCertEx(&x, &k, t->StrValue);

	SetCedarCert(c, x, k);

	ALog(a, NULL, "LA_REGENERATE_SERVER_CERT", t->StrValue);

	IncrementServerConfigRevision(s);

	FreeX(x);
	FreeK(k);

	return ERR_NO_ERROR;
}