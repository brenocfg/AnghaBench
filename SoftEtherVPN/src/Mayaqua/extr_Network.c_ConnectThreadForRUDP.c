#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int Delay; int Ok; int Finished; int /*<<< orphan*/  FinishEvent; int /*<<< orphan*/  FinishedTick; int /*<<< orphan*/ * Result_Nat_T_Sock; int /*<<< orphan*/  TargetHostname; int /*<<< orphan*/  HintStr; int /*<<< orphan*/  CancelFlag; int /*<<< orphan*/  Timeout; int /*<<< orphan*/  NatT_ErrorCode; int /*<<< orphan*/  Ip; int /*<<< orphan*/  SvcName; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  TYPE_1__ CONNECT_TCP_RUDP_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/ * NewRUDPClientNatT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tick64 () ; 
 int /*<<< orphan*/  WaitEx (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void ConnectThreadForRUDP(THREAD *thread, void *param)
{
	SOCK *sock;
	CONNECT_TCP_RUDP_PARAM *p = (CONNECT_TCP_RUDP_PARAM *)param;
	if (thread == NULL || p == NULL)
	{
		return;
	}

	// Delay
	if (p->Delay >= 1)
	{
		WaitEx(NULL, p->Delay, p->CancelFlag);
	}

	// Connecting process
	sock = NewRUDPClientNatT(p->SvcName, &p->Ip, &p->NatT_ErrorCode, p->Timeout, p->CancelFlag, p->HintStr, p->TargetHostname);

	p->Result_Nat_T_Sock = sock;
	p->Ok = (p->Result_Nat_T_Sock == NULL ? false : true);
	p->FinishedTick = Tick64();
	p->Finished = true;

	Set(p->FinishEvent);
}