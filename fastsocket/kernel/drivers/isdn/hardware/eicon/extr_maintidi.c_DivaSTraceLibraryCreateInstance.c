#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  error_notify_proc; int /*<<< orphan*/  trace_proc; int /*<<< orphan*/  notify_proc; int /*<<< orphan*/  user_context; } ;
typedef  TYPE_5__ diva_trace_library_user_interface_t ;
typedef  int /*<<< orphan*/  diva_strace_path2action_t ;
typedef  int /*<<< orphan*/  diva_strace_library_interface_t ;
struct TYPE_13__ {int /*<<< orphan*/ * R; } ;
struct TYPE_11__ {int /*<<< orphan*/  error_notify_proc; int /*<<< orphan*/  trace_proc; int /*<<< orphan*/  notify_proc; int /*<<< orphan*/  user_context; } ;
struct TYPE_10__ {int /*<<< orphan*/  DivaSTraceClearCall; int /*<<< orphan*/  DivaSTraceGetDLayer2Statistics; int /*<<< orphan*/  DivaSTraceGetDLayer1Statistics; int /*<<< orphan*/  DivaSTraceGetBLayer2Statistics; int /*<<< orphan*/  DivaSTraceGetBLayer1Statistics; int /*<<< orphan*/  DivaSTraceGetFaxStatistics; int /*<<< orphan*/  DivaSTraceGetModemStatistics; int /*<<< orphan*/  DivaSTraceGetIncomingCallStatistics; int /*<<< orphan*/  DivaSTraceGetOutgoingCallStatistics; int /*<<< orphan*/  DivaSTraceSetInfo; int /*<<< orphan*/  DivaSTraceSetDChannel; int /*<<< orphan*/  DivaSTraceSetBChannel; int /*<<< orphan*/  DivaSTraceSetAudioTap; int /*<<< orphan*/  DivaSTraceGetHandle; int /*<<< orphan*/  DivaSTraceMessageInput; int /*<<< orphan*/  DivaSTraceLibraryFinit; int /*<<< orphan*/  DivaSTraceLibraryStop; int /*<<< orphan*/  DivaSTraceLibraryStart; TYPE_6__* hLib; } ;
struct TYPE_15__ {int Adapter; int Channels; int parse_entries; int req_busy; int /*<<< orphan*/  rc_ok; int /*<<< orphan*/  RData; TYPE_4__ e; int /*<<< orphan*/  InterfaceStat; TYPE_3__* lines; int /*<<< orphan*/  Interface; int /*<<< orphan*/ * parse_table; int /*<<< orphan*/  hAdapter; TYPE_2__ user_proc_table; TYPE_1__ instance; } ;
typedef  TYPE_6__ diva_strace_context_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_12__ {int /*<<< orphan*/ * pInterfaceStat; int /*<<< orphan*/ * pInterface; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSIGN_OK ; 
 int /*<<< orphan*/  DLI_ERR ; 
 int /*<<< orphan*/  DivaSTraceLibraryStart ; 
 int /*<<< orphan*/  DivaSTraceLibraryStop ; 
 int FAX_PARSE_ENTRIES ; 
 int LINE_PARSE_ENTRIES ; 
 int MODEM_PARSE_ENTRIES ; 
 int STAT_PARSE_ENTRIES ; 
 int /*<<< orphan*/  SuperTraceClearCall ; 
 int /*<<< orphan*/  SuperTraceGetBLayer1Statistics ; 
 int /*<<< orphan*/  SuperTraceGetBLayer2Statistics ; 
 int /*<<< orphan*/  SuperTraceGetDLayer1Statistics ; 
 int /*<<< orphan*/  SuperTraceGetDLayer2Statistics ; 
 int /*<<< orphan*/  SuperTraceGetFaxStatistics ; 
 int /*<<< orphan*/  SuperTraceGetHandle ; 
 int /*<<< orphan*/  SuperTraceGetIncomingCallStatistics ; 
 int /*<<< orphan*/  SuperTraceGetModemStatistics ; 
 int SuperTraceGetNumberOfChannels (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SuperTraceGetOutgoingCallStatistics ; 
 int /*<<< orphan*/  SuperTraceLibraryFinit ; 
 int /*<<< orphan*/  SuperTraceMessageInput ; 
 int /*<<< orphan*/  SuperTraceOpenAdapter (int) ; 
 int /*<<< orphan*/  SuperTraceSetAudioTap ; 
 int /*<<< orphan*/  SuperTraceSetBChannel ; 
 int /*<<< orphan*/  SuperTraceSetDChannel ; 
 int /*<<< orphan*/  SuperTraceSetInfo ; 
 int /*<<< orphan*/  diva_create_parse_table (TYPE_6__*) ; 
 int /*<<< orphan*/  diva_mnt_internal_dprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int,int) ; 

diva_strace_library_interface_t* DivaSTraceLibraryCreateInstance (int Adapter,
											const diva_trace_library_user_interface_t* user_proc,
                      byte* pmem) {
	diva_strace_context_t* pLib = (diva_strace_context_t*)pmem;
	int i;

	if (!pLib) {
		return NULL;
	}

	pmem += sizeof(*pLib);
	memset(pLib, 0x00, sizeof(*pLib));

	pLib->Adapter  = Adapter;

	/*
		Set up Library Interface
		*/
	pLib->instance.hLib                                = pLib;
  pLib->instance.DivaSTraceLibraryStart              = DivaSTraceLibraryStart;
  pLib->instance.DivaSTraceLibraryStop               = DivaSTraceLibraryStop;
	pLib->instance.DivaSTraceLibraryFinit              = SuperTraceLibraryFinit;
	pLib->instance.DivaSTraceMessageInput              = SuperTraceMessageInput;
	pLib->instance.DivaSTraceGetHandle                 = SuperTraceGetHandle;
	pLib->instance.DivaSTraceSetAudioTap               = SuperTraceSetAudioTap;
	pLib->instance.DivaSTraceSetBChannel               = SuperTraceSetBChannel;
	pLib->instance.DivaSTraceSetDChannel               = SuperTraceSetDChannel;
	pLib->instance.DivaSTraceSetInfo                   = SuperTraceSetInfo;
	pLib->instance.DivaSTraceGetOutgoingCallStatistics = \
																			SuperTraceGetOutgoingCallStatistics;
	pLib->instance.DivaSTraceGetIncomingCallStatistics = \
																			SuperTraceGetIncomingCallStatistics;
	pLib->instance.DivaSTraceGetModemStatistics        = \
																			SuperTraceGetModemStatistics;
	pLib->instance.DivaSTraceGetFaxStatistics          = \
																			SuperTraceGetFaxStatistics;
	pLib->instance.DivaSTraceGetBLayer1Statistics      = \
																			SuperTraceGetBLayer1Statistics;
	pLib->instance.DivaSTraceGetBLayer2Statistics      = \
																			SuperTraceGetBLayer2Statistics;
	pLib->instance.DivaSTraceGetDLayer1Statistics      = \
																			SuperTraceGetDLayer1Statistics;
	pLib->instance.DivaSTraceGetDLayer2Statistics      = \
																			SuperTraceGetDLayer2Statistics;
	pLib->instance.DivaSTraceClearCall                 = SuperTraceClearCall;


	if (user_proc) {
		pLib->user_proc_table.user_context      = user_proc->user_context;
		pLib->user_proc_table.notify_proc       = user_proc->notify_proc;
		pLib->user_proc_table.trace_proc        = user_proc->trace_proc;
		pLib->user_proc_table.error_notify_proc = user_proc->error_notify_proc;
	}

	if (!(pLib->hAdapter = SuperTraceOpenAdapter (Adapter))) {
    diva_mnt_internal_dprintf (0, DLI_ERR, "Can not open XDI adapter");
		return NULL;
	}
	pLib->Channels = SuperTraceGetNumberOfChannels (pLib->hAdapter);

	/*
		Calculate amount of parte table entites necessary to translate
		information from all events of onterest
		*/
	pLib->parse_entries = (MODEM_PARSE_ENTRIES + FAX_PARSE_ENTRIES + \
												 STAT_PARSE_ENTRIES + \
												 LINE_PARSE_ENTRIES + 1) * pLib->Channels;
	pLib->parse_table = (diva_strace_path2action_t*)pmem;

	for (i = 0; i < 30; i++) {
		pLib->lines[i].pInterface     = &pLib->Interface;
		pLib->lines[i].pInterfaceStat = &pLib->InterfaceStat;
	}

  pLib->e.R = &pLib->RData;

	pLib->req_busy = 1;
	pLib->rc_ok    = ASSIGN_OK;

	diva_create_parse_table (pLib);

	return ((diva_strace_library_interface_t*)pLib);
}