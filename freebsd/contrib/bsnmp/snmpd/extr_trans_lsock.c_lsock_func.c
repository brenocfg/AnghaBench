#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snmp_dependency {int dummy; } ;
struct snmp_context {int /*<<< orphan*/  code; } ;
struct lsock_dep {int set; int /*<<< orphan*/  path; TYPE_1__* port; int /*<<< orphan*/  status; int /*<<< orphan*/  type; int /*<<< orphan*/  pathlen; } ;
typedef  enum snmp_depop { ____Placeholder_snmp_depop } snmp_depop ;
struct TYPE_2__ {int /*<<< orphan*/  tport; } ;

/* Variables and functions */
 int LD_CREATE ; 
 int LD_DELETE ; 
 int LD_STATUS ; 
#define  SNMP_DEPOP_COMMIT 130 
#define  SNMP_DEPOP_FINISH 129 
#define  SNMP_DEPOP_ROLLBACK 128 
 int SNMP_ERR_BADVALUE ; 
 int SNMP_ERR_NOERROR ; 
 int SNMP_ERR_READONLY ; 
 int /*<<< orphan*/  SNMP_RET_OK ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsock_close_port (int /*<<< orphan*/ *) ; 
 int lsock_open_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lsock_func(struct snmp_context *ctx, struct snmp_dependency *dep,
    enum snmp_depop op)
{
	struct lsock_dep *ld = (struct lsock_dep *)(void *)dep;
	int err = SNMP_ERR_NOERROR;

	switch (op) {

	  case SNMP_DEPOP_COMMIT:
		if (!(ld->set & LD_STATUS))
			err = SNMP_ERR_BADVALUE;
		else if (ld->port == NULL) {
			if (!ld->status)
				err = SNMP_ERR_BADVALUE;

			else {
				/* create */
				err = lsock_open_port(ld->path, ld->pathlen,
				    &ld->port, ld->type);
				if (err == SNMP_ERR_NOERROR)
					ld->set |= LD_CREATE;
			}
		} else if (!ld->status) {
			/* delete - hard to roll back so defer to finalizer */
			ld->set |= LD_DELETE;
		} else
			/* modify - read-only */
			err = SNMP_ERR_READONLY;

		return (err);

	  case SNMP_DEPOP_ROLLBACK:
		if (ld->set & LD_CREATE) {
			/* was create */
			lsock_close_port(&ld->port->tport);
		}
		return (SNMP_ERR_NOERROR);

	  case SNMP_DEPOP_FINISH:
		if ((ld->set & LD_DELETE) && ctx->code == SNMP_RET_OK)
			lsock_close_port(&ld->port->tport);
		free(ld->path);
		return (SNMP_ERR_NOERROR);
	}
	abort();
}