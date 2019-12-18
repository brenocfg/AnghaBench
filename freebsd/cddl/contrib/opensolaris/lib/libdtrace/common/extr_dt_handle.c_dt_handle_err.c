#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  where ;
typedef  int uint32_t ;
typedef  int u_longlong_t ;
typedef  int /*<<< orphan*/  offinfo ;
struct TYPE_14__ {char const* dtpd_provider; char const* dtpd_name; char const* dtpd_mod; char const* dtpd_func; int dtpd_id; } ;
typedef  TYPE_1__ dtrace_probedesc_t ;
struct TYPE_15__ {int /*<<< orphan*/  dtpda_cpu; TYPE_1__* dtpda_pdesc; TYPE_5__* dtpda_edesc; } ;
typedef  TYPE_2__ dtrace_probedata_t ;
struct TYPE_16__ {scalar_t__ (* dt_errhdlr ) (TYPE_4__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dt_errarg; } ;
typedef  TYPE_3__ dtrace_hdl_t ;
struct TYPE_17__ {int dteda_action; int dteda_offset; int dteda_fault; char* dteda_msg; scalar_t__ dteda_addr; int /*<<< orphan*/  dteda_cpu; TYPE_1__* dteda_pdesc; TYPE_5__* dteda_edesc; } ;
typedef  TYPE_4__ dtrace_errdata_t ;
struct TYPE_18__ {scalar_t__ dtepd_uarg; int dtepd_nrecs; } ;
typedef  TYPE_5__ dtrace_eprobedesc_t ;
typedef  int dtrace_epid_t ;

/* Variables and functions */
#define  DTRACEFLT_BADADDR 130 
#define  DTRACEFLT_BADALIGN 129 
#define  DTRACEFLT_BADSTACK 128 
 scalar_t__ DTRACE_HANDLE_ABORT ; 
 scalar_t__ DT_ECB_ERROR ; 
 scalar_t__ DT_REC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EDT_BADERROR ; 
 int /*<<< orphan*/  EDT_ERRABORT ; 
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ dt_epid_lookup (TYPE_3__*,int,TYPE_5__**,TYPE_1__**) ; 
 int dt_set_errno (TYPE_3__*,int /*<<< orphan*/ ) ; 
 char* dtrace_faultstr (TYPE_3__*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,char const*,char const*,char const*,char const*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 
 scalar_t__ stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uint64_t ; 

__attribute__((used)) static int
dt_handle_err(dtrace_hdl_t *dtp, dtrace_probedata_t *data)
{
	dtrace_eprobedesc_t *epd = data->dtpda_edesc, *errepd;
	dtrace_probedesc_t *pd = data->dtpda_pdesc, *errpd;
	dtrace_errdata_t err;
	dtrace_epid_t epid;

	char where[30];
	char details[30];
	char offinfo[30];
	const int slop = 80;
	const char *faultstr;
	char *str;
	int len;

	assert(epd->dtepd_uarg == DT_ECB_ERROR);

	if (epd->dtepd_nrecs != 5 || strcmp(pd->dtpd_provider, "dtrace") != 0 ||
	    strcmp(pd->dtpd_name, "ERROR") != 0)
		return (dt_set_errno(dtp, EDT_BADERROR));

	/*
	 * This is an error.  We have the following items here:  EPID,
	 * faulting action, DIF offset, fault code and faulting address.
	 */
	epid = (uint32_t)DT_REC(uint64_t, 0);

	if (dt_epid_lookup(dtp, epid, &errepd, &errpd) != 0)
		return (dt_set_errno(dtp, EDT_BADERROR));

	err.dteda_edesc = errepd;
	err.dteda_pdesc = errpd;
	err.dteda_cpu = data->dtpda_cpu;
	err.dteda_action = (int)DT_REC(uint64_t, 1);
	err.dteda_offset = (int)DT_REC(uint64_t, 2);
	err.dteda_fault = (int)DT_REC(uint64_t, 3);
	err.dteda_addr = DT_REC(uint64_t, 4);

	faultstr = dtrace_faultstr(dtp, err.dteda_fault);
	len = sizeof (where) + sizeof (offinfo) + strlen(faultstr) +
	    strlen(errpd->dtpd_provider) + strlen(errpd->dtpd_mod) +
	    strlen(errpd->dtpd_name) + strlen(errpd->dtpd_func) +
	    slop;

	str = (char *)alloca(len);

	if (err.dteda_action == 0) {
		(void) sprintf(where, "predicate");
	} else {
		(void) sprintf(where, "action #%d", err.dteda_action);
	}

	if (err.dteda_offset != -1) {
		(void) sprintf(offinfo, " at DIF offset %d", err.dteda_offset);
	} else {
		offinfo[0] = 0;
	}

	switch (err.dteda_fault) {
	case DTRACEFLT_BADADDR:
	case DTRACEFLT_BADALIGN:
	case DTRACEFLT_BADSTACK:
		(void) sprintf(details, " (0x%llx)",
		    (u_longlong_t)err.dteda_addr);
		break;

	default:
		details[0] = 0;
	}

	(void) snprintf(str, len, "error on enabled probe ID %u "
	    "(ID %u: %s:%s:%s:%s): %s%s in %s%s\n",
	    epid, errpd->dtpd_id, errpd->dtpd_provider,
	    errpd->dtpd_mod, errpd->dtpd_func,
	    errpd->dtpd_name, dtrace_faultstr(dtp, err.dteda_fault),
	    details, where, offinfo);

	err.dteda_msg = str;

	if (dtp->dt_errhdlr == NULL)
		return (dt_set_errno(dtp, EDT_ERRABORT));

	if ((*dtp->dt_errhdlr)(&err, dtp->dt_errarg) == DTRACE_HANDLE_ABORT)
		return (dt_set_errno(dtp, EDT_ERRABORT));

	return (0);
}