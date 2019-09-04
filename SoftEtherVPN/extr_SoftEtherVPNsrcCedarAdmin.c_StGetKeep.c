#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_11__ {TYPE_1__* Server; } ;
struct TYPE_10__ {int Interval; int /*<<< orphan*/  lock; int /*<<< orphan*/  UdpMode; int /*<<< orphan*/  ServerPort; int /*<<< orphan*/  ServerName; int /*<<< orphan*/  Enable; } ;
struct TYPE_9__ {int KeepConnectInterval; int /*<<< orphan*/  KeepConnectProtocol; int /*<<< orphan*/  KeepConnectPort; int /*<<< orphan*/  KeepConnectHost; int /*<<< orphan*/  UseKeepConnect; } ;
struct TYPE_8__ {TYPE_3__* Keep; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_KEEP ;
typedef  TYPE_3__ KEEP ;
typedef  TYPE_4__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

UINT StGetKeep(ADMIN *a, RPC_KEEP *t)
{
	SERVER *s = a->Server;

	Zero(t, sizeof(RPC_KEEP));

	Lock(s->Keep->lock);
	{
		KEEP *k = s->Keep;
		t->UseKeepConnect = k->Enable;
		StrCpy(t->KeepConnectHost, sizeof(t->KeepConnectHost), k->ServerName);
		t->KeepConnectPort = k->ServerPort;
		t->KeepConnectProtocol = k->UdpMode;
		t->KeepConnectInterval = k->Interval / 1000;
	}
	Unlock(s->Keep->lock);

	return ERR_NO_ERROR;
}