#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uintmax_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
typedef  int /*<<< orphan*/  dtrace_probedesc_t ;
typedef  int /*<<< orphan*/  dtrace_id_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_5__ {int /*<<< orphan*/ * dn_desc; } ;
typedef  TYPE_1__ dt_node_t ;
struct TYPE_6__ {size_t pcb_pspec; int /*<<< orphan*/  pcb_jmpbuf; int /*<<< orphan*/ * pcb_hdl; } ;

/* Variables and functions */
 size_t DTRACE_PROBESPEC_NAME ; 
 int /*<<< orphan*/  DT_NODE_PDESC ; 
 int /*<<< orphan*/  D_PDESC_INVAL ; 
 int /*<<< orphan*/  EDT_NOMEM ; 
 scalar_t__ UINT_MAX ; 
 TYPE_1__* dt_node_alloc (int /*<<< orphan*/ ) ; 
 char const* const dtrace_errmsg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_errno (int /*<<< orphan*/ *) ; 
 scalar_t__ dtrace_id2desc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 TYPE_2__* yypcb ; 

dt_node_t *
dt_node_pdesc_by_id(uintmax_t id)
{
	static const char *const names[] = {
		"providers", "modules", "functions"
	};

	dtrace_hdl_t *dtp = yypcb->pcb_hdl;
	dt_node_t *dnp = dt_node_alloc(DT_NODE_PDESC);

	if ((dnp->dn_desc = malloc(sizeof (dtrace_probedesc_t))) == NULL)
		longjmp(yypcb->pcb_jmpbuf, EDT_NOMEM);

	if (id > UINT_MAX) {
		xyerror(D_PDESC_INVAL, "identifier %llu exceeds maximum "
		    "probe id\n", (u_longlong_t)id);
	}

	if (yypcb->pcb_pspec != DTRACE_PROBESPEC_NAME) {
		xyerror(D_PDESC_INVAL, "probe identifier %llu not permitted "
		    "when specifying %s\n", (u_longlong_t)id,
		    names[yypcb->pcb_pspec]);
	}

	if (dtrace_id2desc(dtp, (dtrace_id_t)id, dnp->dn_desc) != 0) {
		xyerror(D_PDESC_INVAL, "invalid probe identifier %llu: %s\n",
		    (u_longlong_t)id, dtrace_errmsg(dtp, dtrace_errno(dtp)));
	}

	return (dnp);
}