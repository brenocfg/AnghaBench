#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmdline ;
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int /*<<< orphan*/  ConditionAndArgs; int /*<<< orphan*/  Chain; int /*<<< orphan*/  DummyMark; int /*<<< orphan*/  DummyDestIP; int /*<<< orphan*/  DummySrcIp; } ;
struct TYPE_6__ {int /*<<< orphan*/  EntryList; } ;
typedef  TYPE_1__ IPTABLES_STATE ;
typedef  TYPE_2__ IPTABLES_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  Format (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeIpTablesState (TYPE_1__*) ; 
 scalar_t__ GetCurrentIpTableLineNumber (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  system (char*) ; 

void EndAddIpTablesEntryForNativeStack(IPTABLES_STATE *s)
{
	UINT i;
	if (s == NULL)
	{
		return;
	}

	// Delete entries
	for (i = 0; i < LIST_NUM(s->EntryList);i++)
	{
		IPTABLES_ENTRY *e = LIST_DATA(s->EntryList, i);
		UINT j;

		for (j = 0;j < 100;j++)
		{
			if (GetCurrentIpTableLineNumber(e->Chain, &e->DummySrcIp, &e->DummyDestIP, e->DummyMark) != 0)
			{
				char cmdline[MAX_PATH];

				Format(cmdline, sizeof(cmdline),
					"iptables -D %s %s",
					e->Chain, e->ConditionAndArgs);

				system(cmdline);
			}
			else
			{
				break;
			}
		}
	}

	FreeIpTablesState(s);
}