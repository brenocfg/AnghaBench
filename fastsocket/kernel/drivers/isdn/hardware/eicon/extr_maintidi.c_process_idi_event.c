#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ dword ;
struct TYPE_20__ {int Channels; int trace_events_down; int l1_trace; int l2_trace; TYPE_2__* lines; int /*<<< orphan*/  modem_init_event; int /*<<< orphan*/  pending_modem_status; int /*<<< orphan*/  fax_init_event; int /*<<< orphan*/  pending_fax_status; int /*<<< orphan*/  pending_line_status; int /*<<< orphan*/  line_init_event; } ;
typedef  TYPE_3__ diva_strace_context_t ;
struct TYPE_21__ {int /*<<< orphan*/  path_length; } ;
typedef  TYPE_4__ diva_man_var_header_t ;
struct TYPE_19__ {TYPE_1__* pInterface; } ;
struct TYPE_18__ {char* Layer2; int /*<<< orphan*/ * Layer1; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIVA_SUPER_TRACE_INTERFACE_CHANGE ; 
 int SuperTraceGetIncomingCallStatistics (TYPE_3__*) ; 
 int SuperTraceGetOutgoingCallStatistics (TYPE_3__*) ; 
 int diva_fax_event (TYPE_3__*,int) ; 
 int diva_line_event (TYPE_3__*,int) ; 
 int diva_modem_event (TYPE_3__*,int) ; 
 int /*<<< orphan*/  diva_strace_read_asz (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ diva_strace_read_uint (TYPE_4__*,scalar_t__*) ; 
 int /*<<< orphan*/  diva_trace_error (TYPE_3__*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diva_trace_notify_user (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diva_trace_read_variable (TYPE_4__*,scalar_t__*) ; 
 scalar_t__ find_var (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_idi_event (diva_strace_context_t* pLib,
				diva_man_var_header_t* pVar) {
	const char* path = (char*)&pVar->path_length+1;
	char name[64];
	int i;

	if (!strncmp("State\\B Event", path, pVar->path_length)) {
    dword ch_id;
    if (!diva_trace_read_variable (pVar, &ch_id)) {
      if (!pLib->line_init_event && !pLib->pending_line_status) {
        for (i = 1; i <= pLib->Channels; i++) {
          diva_line_event(pLib, i);
        }
        return (0);
      } else if (ch_id && ch_id <= pLib->Channels) {
        return (diva_line_event(pLib, (int)ch_id));
      }
      return (0);
    }
    return (-1);
  }

	if (!strncmp("State\\FAX Event", path, pVar->path_length)) {
    dword ch_id;
    if (!diva_trace_read_variable (pVar, &ch_id)) {
      if (!pLib->pending_fax_status && !pLib->fax_init_event) {
        for (i = 1; i <= pLib->Channels; i++) {
          diva_fax_event(pLib, i);
        }
        return (0);
      } else if (ch_id && ch_id <= pLib->Channels) {
        return (diva_fax_event(pLib, (int)ch_id));
      }
      return (0);
    }
    return (-1);
  }

	if (!strncmp("State\\Modem Event", path, pVar->path_length)) {
    dword ch_id;
    if (!diva_trace_read_variable (pVar, &ch_id)) {
      if (!pLib->pending_modem_status && !pLib->modem_init_event) {
        for (i = 1; i <= pLib->Channels; i++) {
          diva_modem_event(pLib, i);
        }
        return (0);
      } else if (ch_id && ch_id <= pLib->Channels) {
        return (diva_modem_event(pLib, (int)ch_id));
      }
      return (0);
    }
    return (-1);
  }

	/*
		First look for Line Event
		*/
	for (i = 1; i <= pLib->Channels; i++) {
		sprintf (name, "State\\B%d\\Line", i);
		if (find_var (pVar, name)) {
			return (diva_line_event(pLib, i));
		}
	}

	/*
		Look for Moden Progress Event
		*/
	for (i = 1; i <= pLib->Channels; i++) {
		sprintf (name, "State\\B%d\\Modem\\Event", i);
		if (find_var (pVar, name)) {
			return (diva_modem_event (pLib, i));
		}
	}

	/*
		Look for Fax Event
		*/
	for (i = 1; i <= pLib->Channels; i++) {
		sprintf (name, "State\\B%d\\FAX\\Event", i);
		if (find_var (pVar, name)) {
			return (diva_fax_event (pLib, i));
		}
	}

	/*
		Notification about loss of events
		*/
	if (!strncmp("Events Down", path, pVar->path_length)) {
		if (pLib->trace_events_down == 1) {
			pLib->trace_events_down = 2;
		} else {
			diva_trace_error (pLib, 1, "Events Down", 0);
		}
		return (0);
	}

	if (!strncmp("State\\Layer1", path, pVar->path_length)) {
		diva_strace_read_asz  (pVar, &pLib->lines[0].pInterface->Layer1[0]);
		if (pLib->l1_trace == 1) {
			pLib->l1_trace = 2;
		} else {
			diva_trace_notify_user (pLib, 0, DIVA_SUPER_TRACE_INTERFACE_CHANGE);
		}
		return (0);
	}
	if (!strncmp("State\\Layer2 No1", path, pVar->path_length)) {
		char* tmp = &pLib->lines[0].pInterface->Layer2[0];
		dword l2_state;
		if (diva_strace_read_uint(pVar, &l2_state))
			return -1;

		switch (l2_state) {
			case 0:
				strcpy (tmp, "Idle");
				break;
			case 1:
				strcpy (tmp, "Layer2 UP");
				break;
			case 2:
				strcpy (tmp, "Layer2 Disconnecting");
				break;
			case 3:
				strcpy (tmp, "Layer2 Connecting");
				break;
			case 4:
				strcpy (tmp, "SPID Initializing");
				break;
			case 5:
				strcpy (tmp, "SPID Initialised");
				break;
			case 6:
				strcpy (tmp, "Layer2 Connecting");
				break;

			case  7:
				strcpy (tmp, "Auto SPID Stopped");
				break;

			case  8:
				strcpy (tmp, "Auto SPID Idle");
				break;

			case  9:
				strcpy (tmp, "Auto SPID Requested");
				break;

			case  10:
				strcpy (tmp, "Auto SPID Delivery");
				break;

			case 11:
				strcpy (tmp, "Auto SPID Complete");
				break;

			default:
				sprintf (tmp, "U:%d", (int)l2_state);
		}
		if (pLib->l2_trace == 1) {
			pLib->l2_trace = 2;
		} else {
			diva_trace_notify_user (pLib, 0, DIVA_SUPER_TRACE_INTERFACE_CHANGE);
		}
		return (0);
	}

	if (!strncmp("Statistics\\Incoming Calls\\Calls", path, pVar->path_length) ||
			!strncmp("Statistics\\Incoming Calls\\Connected", path, pVar->path_length)) {
		return (SuperTraceGetIncomingCallStatistics (pLib));
	}

	if (!strncmp("Statistics\\Outgoing Calls\\Calls", path, pVar->path_length) ||
			!strncmp("Statistics\\Outgoing Calls\\Connected", path, pVar->path_length)) {
		return (SuperTraceGetOutgoingCallStatistics (pLib));
	}

	return (-1);
}