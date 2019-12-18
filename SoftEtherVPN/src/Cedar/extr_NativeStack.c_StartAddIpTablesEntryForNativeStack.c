#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmdline ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/  DummyMark; int /*<<< orphan*/  DummyDestIP; int /*<<< orphan*/  DummySrcIp; int /*<<< orphan*/  Chain; int /*<<< orphan*/  ConditionAndArgs; } ;
struct TYPE_8__ {int /*<<< orphan*/  EntryList; int /*<<< orphan*/  SeedHash; } ;
typedef  TYPE_1__ IPTABLES_STATE ;
typedef  TYPE_2__ IPTABLES_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  Debug (char*,char*) ; 
 int /*<<< orphan*/  EndAddIpTablesEntryForNativeStack (TYPE_1__*) ; 
 int /*<<< orphan*/  Format (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  GenerateDummyIpAndMark (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 scalar_t__ GetCurrentIpTableLineNumber (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IsIpTablesSupported () ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  NN_RAW_IP_PORT_END ; 
 int /*<<< orphan*/  NN_RAW_IP_PORT_START ; 
 int /*<<< orphan*/  NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Sha1 (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 void* ZeroMalloc (int) ; 
 int /*<<< orphan*/  system (char*) ; 

IPTABLES_STATE *StartAddIpTablesEntryForNativeStack(void *seed, UINT seed_size)
{
	IPTABLES_STATE *ret = NULL;
	bool ok = false;

	if (IsIpTablesSupported())
	{
		IPTABLES_ENTRY *e;
		UINT i;

		ret = ZeroMalloc(sizeof(IPTABLES_STATE));

		ret->EntryList = NewListFast(NULL);

		Sha1(ret->SeedHash, seed, seed_size);

		// Create a pair of entry
		e = ZeroMalloc(sizeof(IPTABLES_ENTRY));
		GenerateDummyIpAndMark(ret->SeedHash, e, 0);
		StrCpy(e->Chain, sizeof(e->Chain), "OUTPUT");
		Format(e->ConditionAndArgs, sizeof(e->ConditionAndArgs),
			"-p tcp --tcp-flags RST RST --sport %u:%u ! -s %r/32 ! -d %r/32 -m connmark ! --mark 0x%x -j DROP",
			NN_RAW_IP_PORT_START, NN_RAW_IP_PORT_END,
			&e->DummySrcIp, &e->DummyDestIP, e->DummyMark);
		Add(ret->EntryList, e);

		e = ZeroMalloc(sizeof(IPTABLES_ENTRY));
		GenerateDummyIpAndMark(ret->SeedHash, e, 1);
		StrCpy(e->Chain, sizeof(e->Chain), "OUTPUT");
		Format(e->ConditionAndArgs, sizeof(e->ConditionAndArgs),
			"-p icmp --icmp-type 3/3 ! -s %r/32 ! -d %r/32 -m connmark ! --mark 0x%x -j DROP",
			&e->DummySrcIp, &e->DummyDestIP, e->DummyMark);
		Add(ret->EntryList, e);

		ok = true;

		// Insert entries if not exists
		for (i = 0; i < LIST_NUM(ret->EntryList);i++)
		{
			UINT j;
			IPTABLES_ENTRY *e = LIST_DATA(ret->EntryList, i);

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

			if (GetCurrentIpTableLineNumber(e->Chain, &e->DummySrcIp, &e->DummyDestIP, e->DummyMark) == 0)
			{
				char cmdline[MAX_PATH];

				Format(cmdline, sizeof(cmdline),
					"iptables -I %s %s",
					e->Chain, e->ConditionAndArgs);

				system(cmdline);

				if (GetCurrentIpTableLineNumber(e->Chain, &e->DummySrcIp, &e->DummyDestIP, e->DummyMark) == 0)
				{
					Debug("Run \"%s\" failed.\n", cmdline);
					ok = false;
					break;
				}
				else
				{
					Debug("Run \"%s\" ok.\n", cmdline);
				}
			}
		}
	}

	if (ok == false)
	{
		EndAddIpTablesEntryForNativeStack(ret);
		ret = NULL;
	}

	return ret;
}