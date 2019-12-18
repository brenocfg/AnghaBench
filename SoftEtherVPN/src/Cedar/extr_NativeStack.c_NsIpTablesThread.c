#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  exe_name ;
typedef  int UINT ;
struct TYPE_8__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_7__ {int IpTablesInitOk; int /*<<< orphan*/  IpTablesHaltEvent; scalar_t__ IpTablesHalt; int /*<<< orphan*/  MacAddress; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ NATIVE_STACK ;
typedef  int /*<<< orphan*/  IPTABLES_STATE ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  EndAddIpTablesEntryForNativeStack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 int /*<<< orphan*/  GetExeName (char*,int) ; 
 int MAX_PATH ; 
 int MIN (int,int /*<<< orphan*/ ) ; 
 scalar_t__ MaintainAddIpTablesEntryForNativeStack (int /*<<< orphan*/ *) ; 
 int NS_CHECK_IPTABLES_INTERVAL_INIT ; 
 int /*<<< orphan*/  NS_CHECK_IPTABLES_INTERVAL_MAX ; 
 TYPE_2__* NewBuf () ; 
 int /*<<< orphan*/  NoticeThreadInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * StartAddIpTablesEntryForNativeStack (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WriteBufStr (TYPE_2__*,char*) ; 

void NsIpTablesThread(THREAD *thread, void *param)
{
	IPTABLES_STATE *state;
	NATIVE_STACK *s;
	UINT counter = 0;
	BUF *seed_buf;
	char exe_name[MAX_PATH];
	if (thread == NULL || param == NULL)
	{
		return;
	}

	s = (NATIVE_STACK *)param;

	seed_buf = NewBuf();

	WriteBuf(seed_buf, s->MacAddress, 6);

	GetExeName(exe_name, sizeof(exe_name));
	WriteBufStr(seed_buf, exe_name);

	state = StartAddIpTablesEntryForNativeStack(seed_buf->Buf, seed_buf->Size);

	FreeBuf(seed_buf);

	if (state == NULL)
	{
		NoticeThreadInit(thread);
		return;
	}

	s->IpTablesInitOk = true;
	NoticeThreadInit(thread);

	while (true)
	{
		UINT wait_interval;

		if (s->IpTablesHalt)
		{
			break;
		}

		if (MaintainAddIpTablesEntryForNativeStack(state))
		{
			counter = 0;
		}

		counter++;
		wait_interval = NS_CHECK_IPTABLES_INTERVAL_INIT * counter;
		wait_interval = MIN(wait_interval, NS_CHECK_IPTABLES_INTERVAL_MAX);

		//Debug("NsIpTablesThread: wait for %u\n", wait_interval);
		Wait(s->IpTablesHaltEvent, wait_interval);
	}

	EndAddIpTablesEntryForNativeStack(state);
}