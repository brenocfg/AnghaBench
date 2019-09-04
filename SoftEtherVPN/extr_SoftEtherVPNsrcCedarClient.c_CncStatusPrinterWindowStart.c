#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_4__* Session; TYPE_3__* Sock; } ;
struct TYPE_16__ {TYPE_2__* Account; } ;
struct TYPE_15__ {TYPE_5__* Param; } ;
struct TYPE_14__ {TYPE_1__* ClientOption; } ;
struct TYPE_13__ {int /*<<< orphan*/  AccountName; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_3__ SOCK ;
typedef  TYPE_4__ SESSION ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_5__ CNC_STATUS_PRINTER_WINDOW_PARAM ;

/* Variables and functions */
 TYPE_3__* CncConnect () ; 
 int /*<<< orphan*/  CncStatusPrinterWindowThreadProc ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  PackAddUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_3__*) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int SendPack (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ *) ; 
 TYPE_5__* ZeroMalloc (int) ; 

SOCK *CncStatusPrinterWindowStart(SESSION *s)
{
	SOCK *sock;
	PACK *p;
	THREAD *t;
	CNC_STATUS_PRINTER_WINDOW_PARAM *param;
	// Validate arguments
	if (s == NULL)
	{
		return NULL;
	}

	sock = CncConnect();

	if (sock == NULL)
	{
		return NULL;
	}

	p = NewPack();
	PackAddStr(p, "function", "status_printer");
	PackAddUniStr(p, "account_name", s->Account->ClientOption->AccountName);

	if (SendPack(sock, p) == false)
	{
		FreePack(p);
		ReleaseSock(sock);

		return NULL;
	}

	FreePack(p);

	param = ZeroMalloc(sizeof(CNC_STATUS_PRINTER_WINDOW_PARAM));
	param->Sock = sock;
	param->Session = s;

	sock->Param = param;

	t = NewThread(CncStatusPrinterWindowThreadProc, param);
	WaitThreadInit(t);

	ReleaseThread(t);

	return sock;
}