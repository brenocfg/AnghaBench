#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int pid_t ;
struct TYPE_3__ {char* dtpd_provider; } ;
typedef  TYPE_1__ dtrace_probedesc_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dt_proc_t ;
typedef  int /*<<< orphan*/  dt_pcb_t ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROC_BADPID ; 
 int /*<<< orphan*/  D_PROC_BADPROV ; 
 int /*<<< orphan*/  dt_pid_error (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int strtol (char*,char**,int) ; 

__attribute__((used)) static pid_t
dt_pid_get_pid(dtrace_probedesc_t *pdp, dtrace_hdl_t *dtp, dt_pcb_t *pcb,
    dt_proc_t *dpr)
{
	pid_t pid;
	char *c, *last = NULL, *end;

	for (c = &pdp->dtpd_provider[0]; *c != '\0'; c++) {
		if (!isdigit(*c))
			last = c;
	}

	if (last == NULL || (*(++last) == '\0')) {
		(void) dt_pid_error(dtp, pcb, dpr, NULL, D_PROC_BADPROV,
		    "'%s' is not a valid provider", pdp->dtpd_provider);
		return (-1);
	}

	errno = 0;
	pid = strtol(last, &end, 10);

	if (errno != 0 || end == last || end[0] != '\0' || pid <= 0) {
		(void) dt_pid_error(dtp, pcb, dpr, NULL, D_PROC_BADPID,
		    "'%s' does not contain a valid pid", pdp->dtpd_provider);
		return (-1);
	}

	return (pid);
}