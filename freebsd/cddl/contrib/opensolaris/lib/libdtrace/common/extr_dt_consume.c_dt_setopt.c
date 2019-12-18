#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  optdata ;
struct TYPE_4__ {char const* dtsda_option; int /*<<< orphan*/ * dtsda_handle; int /*<<< orphan*/  const* dtsda_probe; int /*<<< orphan*/  dtsda_newval; int /*<<< orphan*/  dtsda_oldval; } ;
typedef  TYPE_1__ dtrace_setoptdata_t ;
typedef  int /*<<< orphan*/  dtrace_probedata_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;

/* Variables and functions */
 char* alloca (int) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int dt_handle_liberr (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char*) ; 
 int dt_handle_setopt (int /*<<< orphan*/ *,TYPE_1__*) ; 
 char* dtrace_errmsg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_errno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_getopt (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ dtrace_setopt (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*,char const*) ; 
 int strlen (char const*) ; 

int
dt_setopt(dtrace_hdl_t *dtp, const dtrace_probedata_t *data,
    const char *option, const char *value)
{
	int len, rval;
	char *msg;
	const char *errstr;
	dtrace_setoptdata_t optdata;

	bzero(&optdata, sizeof (optdata));
	(void) dtrace_getopt(dtp, option, &optdata.dtsda_oldval);

	if (dtrace_setopt(dtp, option, value) == 0) {
		(void) dtrace_getopt(dtp, option, &optdata.dtsda_newval);
		optdata.dtsda_probe = data;
		optdata.dtsda_option = option;
		optdata.dtsda_handle = dtp;

		if ((rval = dt_handle_setopt(dtp, &optdata)) != 0)
			return (rval);

		return (0);
	}

	errstr = dtrace_errmsg(dtp, dtrace_errno(dtp));
	len = strlen(option) + strlen(value) + strlen(errstr) + 80;
	msg = alloca(len);

	(void) snprintf(msg, len, "couldn't set option \"%s\" to \"%s\": %s\n",
	    option, value, errstr);

	if ((rval = dt_handle_liberr(dtp, data, msg)) == 0)
		return (0);

	return (rval);
}