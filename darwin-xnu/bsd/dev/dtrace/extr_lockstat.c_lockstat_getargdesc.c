#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* lsp_args; } ;
typedef  TYPE_1__ lockstat_probe_t ;
typedef  int /*<<< orphan*/  dtrace_id_t ;
struct TYPE_5__ {char* dtargd_native; char* dtargd_xlate; int dtargd_ndx; } ;
typedef  TYPE_2__ dtrace_argdesc_t ;

/* Variables and functions */
 int DTRACE_ARGNONE ; 
 int /*<<< orphan*/  DTRACE_ARGTYPELEN ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
lockstat_getargdesc(void *arg, dtrace_id_t id, void *parg, dtrace_argdesc_t *desc)
{
#pragma unused(arg, id)
	lockstat_probe_t *probe = parg;
	const char* argdesc = probe->lsp_args;
	int narg = 0;

	desc->dtargd_native[0] = '\0';
	desc->dtargd_xlate[0] = '\0';

	while(argdesc[0] != '\0') {
		if (narg == desc->dtargd_ndx) {
			strlcpy(desc->dtargd_native, argdesc, DTRACE_ARGTYPELEN);
			return;
		}
		argdesc += strlen(argdesc) + 1;
		narg++;
	}

	desc->dtargd_ndx = DTRACE_ARGNONE;
}