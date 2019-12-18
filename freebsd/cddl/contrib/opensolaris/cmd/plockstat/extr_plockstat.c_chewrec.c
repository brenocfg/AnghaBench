#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
struct TYPE_6__ {int dtrd_action; scalar_t__ dtrd_offset; int /*<<< orphan*/  dtrd_uarg; } ;
typedef  TYPE_1__ dtrace_recdesc_t ;
struct TYPE_7__ {scalar_t__ dtpda_data; TYPE_3__* dtpda_edesc; } ;
typedef  TYPE_2__ dtrace_probedata_t ;
struct TYPE_8__ {int /*<<< orphan*/  dtepd_nrecs; } ;
typedef  TYPE_3__ dtrace_eprobedesc_t ;
typedef  int /*<<< orphan*/  dtrace_aggvarid_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
#define  DTRACEACT_DIFEXPR 129 
#define  DTRACEACT_PRINTA 128 
 int DTRACE_CONSUME_NEXT ; 
 int DTRACE_CONSUME_THIS ; 
 int /*<<< orphan*/  dfatal (char*) ; 
 int /*<<< orphan*/  dtrace_aggregate_walk_joined (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_dtp ; 
 int /*<<< orphan*/  g_opt_s ; 
 int /*<<< orphan*/  print_bar () ; 
 int /*<<< orphan*/  print_legend () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  process_aggregate ; 

__attribute__((used)) static int
chewrec(const dtrace_probedata_t *data, const dtrace_recdesc_t *rec, void *arg)
{
	dtrace_eprobedesc_t *epd = data->dtpda_edesc;
	dtrace_aggvarid_t aggvars[2];
	const void *buf;
	int i, nagv;

	/*
	 * A NULL rec indicates that we've processed the last record.
	 */
	if (rec == NULL)
		return (DTRACE_CONSUME_NEXT);

	buf = data->dtpda_data - rec->dtrd_offset;

	switch (rec->dtrd_action) {
	case DTRACEACT_DIFEXPR:
		(void) printf("\n%s\n\n", (char *)buf + rec->dtrd_offset);
		if (!g_opt_s) {
			print_legend();
			print_bar();
		}
		return (DTRACE_CONSUME_NEXT);

	case DTRACEACT_PRINTA:
		for (nagv = 0, i = 0; i < epd->dtepd_nrecs - 1; i++) {
			const dtrace_recdesc_t *nrec = &rec[i];

			if (nrec->dtrd_uarg != rec->dtrd_uarg)
				break;

			/*LINTED - alignment*/
			aggvars[nagv++] = *(dtrace_aggvarid_t *)((caddr_t)buf +
			    nrec->dtrd_offset);
		}

		if (nagv == (g_opt_s ? 1 : 2)) {
			uint_t nent = 0;
			if (dtrace_aggregate_walk_joined(g_dtp, aggvars, nagv,
			    process_aggregate, &nent) != 0)
				dfatal("failed to walk aggregate");
		}

		return (DTRACE_CONSUME_NEXT);
	}

	return (DTRACE_CONSUME_THIS);
}