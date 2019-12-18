#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int Channels; } ;
typedef  TYPE_1__ diva_strace_context_t ;
struct TYPE_14__ {int /*<<< orphan*/  path_length; } ;
typedef  TYPE_2__ diva_man_var_header_t ;

/* Variables and functions */
 int diva_fax_info (TYPE_1__*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  diva_ifc_statistics (TYPE_1__*,TYPE_2__*) ; 
 int diva_line_info (TYPE_1__*,int,TYPE_2__*) ; 
 int diva_modem_info (TYPE_1__*,int,TYPE_2__*) ; 
 int sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int) ; 

__attribute__((used)) static int process_idi_info  (diva_strace_context_t* pLib,
															diva_man_var_header_t* pVar) {
	const char* path = (char*)&pVar->path_length+1;
	char name[64];
	int i, len;

	/*
		First look for Modem Status Info
		*/
	for (i = pLib->Channels; i > 0; i--) {
		len = sprintf (name, "State\\B%d\\Modem", i);
		if (!strncmp(name, path, len)) {
			return (diva_modem_info (pLib, i, pVar));
		}
	}

	/*
		Look for Fax Status Info
		*/
	for (i = pLib->Channels; i > 0; i--) {
		len = sprintf (name, "State\\B%d\\FAX", i);
		if (!strncmp(name, path, len)) {
			return (diva_fax_info (pLib, i, pVar));
		}
	}

	/*
		Look for Line Status Info
		*/
	for (i = pLib->Channels; i > 0; i--) {
		len = sprintf (name, "State\\B%d", i);
		if (!strncmp(name, path, len)) {
			return (diva_line_info (pLib, i, pVar));
		}
	}

	if (!diva_ifc_statistics (pLib, pVar)) {
		return (0);
	}

	return (-1);
}