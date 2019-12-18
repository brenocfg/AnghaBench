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
struct TYPE_4__ {int /*<<< orphan*/  prof_kind; } ;
typedef  TYPE_1__ profile_probe_t ;
typedef  int /*<<< orphan*/  dtrace_id_t ;
struct TYPE_5__ {int dtargd_ndx; int /*<<< orphan*/  dtargd_native; } ;
typedef  TYPE_2__ dtrace_argdesc_t ;

/* Variables and functions */
 int DTRACE_ARGNONE ; 
 int /*<<< orphan*/  DTRACE_ARGTYPELEN ; 
 int /*<<< orphan*/  PROF_PROFILE ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
profile_getargdesc(void *arg, dtrace_id_t id, void *parg, dtrace_argdesc_t *desc)
{
#pragma unused(arg, id)
	profile_probe_t *prof = parg;
	const char *argdesc = NULL;
	switch (desc->dtargd_ndx) {
		case 0:
			argdesc = "void*";
			break;
		case 1:
			argdesc = "user_addr_t";
			break;
		case 2:
			if (prof->prof_kind == PROF_PROFILE) {
				argdesc = "hrtime_t";
			}
			break;
	}
	if (argdesc) {
		strlcpy(desc->dtargd_native, argdesc, DTRACE_ARGTYPELEN);
	}
	else {
		desc->dtargd_ndx = DTRACE_ARGNONE;
	}
}