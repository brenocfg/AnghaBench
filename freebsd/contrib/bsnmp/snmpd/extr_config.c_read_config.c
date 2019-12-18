#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct lmodule {int dummy; } ;
struct TYPE_9__ {TYPE_1__* dep; } ;
struct TYPE_8__ {int /*<<< orphan*/  idx; int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int ASN_OIDSTRLEN ; 
 int /*<<< orphan*/  COMM_INITIALIZE ; 
 int /*<<< orphan*/  ERRPOP () ; 
 scalar_t__ ERRPUSH () ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int SNMP_ERR_NOERROR ; 
 int /*<<< orphan*/  asn_oid2str_r (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  community ; 
 int /*<<< orphan*/  do_commit () ; 
 int /*<<< orphan*/  do_rollback () ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ ignore ; 
 int /*<<< orphan*/  input_close_all () ; 
 int input_open_file (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ input_push ; 
 int /*<<< orphan*/  macro_free_all () ; 
 int /*<<< orphan*/  parse_file (struct lmodule*) ; 
 TYPE_2__* snmp_ctx ; 
 int snmp_dep_commit (TYPE_2__*) ; 
 int /*<<< orphan*/  snmp_dep_finish (TYPE_2__*) ; 
 int /*<<< orphan*/  snmp_dep_rollback (TYPE_2__*) ; 
 TYPE_2__* snmp_init_context () ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

int
read_config(const char *fname, struct lmodule *lodmod)
{
	int err;
	char objbuf[ASN_OIDSTRLEN];
	char idxbuf[ASN_OIDSTRLEN];

	ignore = 0;

	input_push = 0;

	if (ERRPUSH())
		return (-1);
	if (input_open_file(fname, 0) == -1) {
		syslog(LOG_ERR, "%s: %m", fname);
		return (-1);
	}
	ERRPOP();
	community = COMM_INITIALIZE;

	if ((snmp_ctx = snmp_init_context()) == NULL) {
		input_close_all();
		syslog(LOG_ERR, "%m");
		return (-1);
	}

	if (ERRPUSH()) {
		do_rollback();
		input_close_all();
		macro_free_all();
		free(snmp_ctx);
		return (-1);
	}
	parse_file(lodmod);
	ERRPOP();

	if ((err = snmp_dep_commit(snmp_ctx)) != SNMP_ERR_NOERROR) {
		syslog(LOG_ERR, "init dep failed: %u %s %s", err,
		    asn_oid2str_r(&snmp_ctx->dep->obj, objbuf),
		    asn_oid2str_r(&snmp_ctx->dep->idx, idxbuf));
		snmp_dep_rollback(snmp_ctx);
		do_rollback();
		input_close_all();
		macro_free_all();
		free(snmp_ctx);
		return (-1);
	}

	do_commit();
	snmp_dep_finish(snmp_ctx);

	macro_free_all();

	free(snmp_ctx);

	return (0);
}