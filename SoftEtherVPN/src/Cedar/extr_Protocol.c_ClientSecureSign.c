#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X ;
typedef  scalar_t__ UINT64 ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_19__ {int /*<<< orphan*/  SecureSignProc; int /*<<< orphan*/  SecurePublicCertName; int /*<<< orphan*/  SecurePrivateKeyName; } ;
struct TYPE_18__ {int /*<<< orphan*/  ServerName; TYPE_2__* Cedar; TYPE_3__* Session; } ;
struct TYPE_17__ {int Ok; struct TYPE_17__* SecureSign; int /*<<< orphan*/ * ClientCert; int /*<<< orphan*/ * Signature; scalar_t__ UserFinished; int /*<<< orphan*/  SecureSignProc; int /*<<< orphan*/  BitmapId; int /*<<< orphan*/ * Random; int /*<<< orphan*/  UseSecureDeviceId; int /*<<< orphan*/  SecurePublicCertName; int /*<<< orphan*/  SecurePrivateKeyName; TYPE_6__* Connection; } ;
struct TYPE_16__ {TYPE_7__* ClientAuth; int /*<<< orphan*/ * ClientOption; } ;
struct TYPE_15__ {TYPE_1__* Client; } ;
struct TYPE_14__ {int /*<<< orphan*/  UseSecureDeviceId; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_3__ SESSION ;
typedef  TYPE_4__ SECURE_SIGN_THREAD_PROC ;
typedef  TYPE_4__ SECURE_SIGN ;
typedef  TYPE_6__ CONNECTION ;
typedef  int /*<<< orphan*/  CLIENT_OPTION ;
typedef  TYPE_7__ CLIENT_AUTH ;

/* Variables and functions */
 scalar_t__ CONNECTING_POOLING_SPAN ; 
 int /*<<< orphan*/  ClientSecureSignThread ; 
 int /*<<< orphan*/  ClientUploadNoop (TYPE_6__*) ; 
 int /*<<< orphan*/  CmGetSecureBitmapId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Free (TYPE_4__*) ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ *) ; 
 TYPE_4__* ZeroMalloc (int) ; 
 TYPE_4__* ZeroMallocEx (int,int) ; 

bool ClientSecureSign(CONNECTION *c, UCHAR *sign, UCHAR *random, X **x)
{
	SECURE_SIGN_THREAD_PROC *p;
	SECURE_SIGN *ss;
	SESSION *s;
	CLIENT_OPTION *o;
	CLIENT_AUTH *a;
	THREAD *thread;
	UINT64 start;
	bool ret;
	// Validate arguments
	if (c == NULL || sign == NULL || random == NULL || x == NULL)
	{
		return false;
	}

	s = c->Session;
	o = s->ClientOption;
	a = s->ClientAuth;

	p = ZeroMalloc(sizeof(SECURE_SIGN_THREAD_PROC));
	p->Connection = c;
	ss = p->SecureSign = ZeroMallocEx(sizeof(SECURE_SIGN), true);
	StrCpy(ss->SecurePrivateKeyName, sizeof(ss->SecurePrivateKeyName),
		a->SecurePrivateKeyName);
	StrCpy(ss->SecurePublicCertName, sizeof(ss->SecurePublicCertName),
		a->SecurePublicCertName);
	ss->UseSecureDeviceId = c->Cedar->Client->UseSecureDeviceId;
	Copy(ss->Random, random, SHA1_SIZE);

#ifdef	OS_WIN32
	ss->BitmapId = CmGetSecureBitmapId(c->ServerName);
#endif	// OS_WIN32

	p->SecureSignProc = a->SecureSignProc;

	// Create a thread
	thread = NewThread(ClientSecureSignThread, p);
	WaitThreadInit(thread);

	// Poll every 0.5 seconds until signing is completed or canceled
	start = Tick64();
	while (true)
	{
		if ((Tick64() - start) > CONNECTING_POOLING_SPAN)
		{
			// Send a NOOP periodically for disconnection prevention
			start = Tick64();
			ClientUploadNoop(c);
		}
		if (p->UserFinished)
		{
			// User selected
			break;
		}
		WaitThread(thread, 500);
	}
	ReleaseThread(thread);

	ret = p->Ok;

	if (ret)
	{
		Copy(sign, ss->Signature, sizeof(ss->Signature));
		*x = ss->ClientCert;
	}

	Free(p->SecureSign);
	Free(p);

	return ret;
}