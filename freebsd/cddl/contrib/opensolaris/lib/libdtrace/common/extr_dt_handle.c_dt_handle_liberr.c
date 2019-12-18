#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char const* dtpd_provider; char const* dtpd_mod; char const* dtpd_name; char const* dtpd_func; int dtpd_id; } ;
typedef  TYPE_2__ dtrace_probedesc_t ;
struct TYPE_12__ {TYPE_1__* dtpda_edesc; int /*<<< orphan*/  dtpda_cpu; TYPE_2__* dtpda_pdesc; } ;
typedef  TYPE_3__ dtrace_probedata_t ;
struct TYPE_13__ {scalar_t__ (* dt_errhdlr ) (TYPE_5__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dt_errarg; } ;
typedef  TYPE_4__ dtrace_hdl_t ;
struct TYPE_14__ {int dteda_action; int dteda_offset; char* dteda_msg; scalar_t__ dteda_addr; int /*<<< orphan*/  dteda_fault; int /*<<< orphan*/  dteda_cpu; TYPE_2__* dteda_pdesc; TYPE_1__* dteda_edesc; } ;
typedef  TYPE_5__ dtrace_errdata_t ;
struct TYPE_10__ {int dtepd_epid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACEFLT_LIBRARY ; 
 scalar_t__ DTRACE_HANDLE_ABORT ; 
 int /*<<< orphan*/  EDT_ERRABORT ; 
 char* alloca (int) ; 
 int dt_set_errno (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,char const*,char const*,char const*,char const*,char const*) ; 
 int const strlen (char const*) ; 
 scalar_t__ stub1 (TYPE_5__*,int /*<<< orphan*/ ) ; 

int
dt_handle_liberr(dtrace_hdl_t *dtp, const dtrace_probedata_t *data,
    const char *faultstr)
{
	dtrace_probedesc_t *errpd = data->dtpda_pdesc;
	dtrace_errdata_t err;
	const int slop = 80;
	char *str;
	int len;

	err.dteda_edesc = data->dtpda_edesc;
	err.dteda_pdesc = errpd;
	err.dteda_cpu = data->dtpda_cpu;
	err.dteda_action = -1;
	err.dteda_offset = -1;
	err.dteda_fault = DTRACEFLT_LIBRARY;
	err.dteda_addr = 0;

	len = strlen(faultstr) +
	    strlen(errpd->dtpd_provider) + strlen(errpd->dtpd_mod) +
	    strlen(errpd->dtpd_name) + strlen(errpd->dtpd_func) +
	    slop;

	str = alloca(len);

	(void) snprintf(str, len, "error on enabled probe ID %u "
	    "(ID %u: %s:%s:%s:%s): %s\n",
	    data->dtpda_edesc->dtepd_epid,
	    errpd->dtpd_id, errpd->dtpd_provider,
	    errpd->dtpd_mod, errpd->dtpd_func,
	    errpd->dtpd_name, faultstr);

	err.dteda_msg = str;

	if (dtp->dt_errhdlr == NULL)
		return (dt_set_errno(dtp, EDT_ERRABORT));

	if ((*dtp->dt_errhdlr)(&err, dtp->dt_errarg) == DTRACE_HANDLE_ABORT)
		return (dt_set_errno(dtp, EDT_ERRABORT));

	return (0);
}