#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_9__ {int integer; } ;
struct TYPE_10__ {int* subs; int /*<<< orphan*/  len; } ;
struct snmp_value {TYPE_2__ v; TYPE_3__ var; } ;
struct snmp_context {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  index; } ;
struct lsock_port {int type; TYPE_1__ tport; } ;
struct lsock_dep {size_t pathlen; int set; int type; int /*<<< orphan*/  status; struct lsock_port* port; int /*<<< orphan*/ * path; } ;
struct asn_oid {int dummy; } ;
typedef  enum snmp_op { ____Placeholder_snmp_op } snmp_op ;
typedef  int asn_subid_t ;

/* Variables and functions */
 int LD_STATUS ; 
 int LD_TYPE ; 
#define  LEAF_begemotSnmpdLocalPortStatus 134 
#define  LEAF_begemotSnmpdLocalPortType 133 
 int SNMP_ERR_GENERR ; 
 int SNMP_ERR_INCONS_VALUE ; 
 int SNMP_ERR_NOERROR ; 
 int SNMP_ERR_NOSUCHNAME ; 
 int SNMP_ERR_NO_CREATION ; 
 int SNMP_ERR_WRONG_VALUE ; 
#define  SNMP_OP_COMMIT 132 
#define  SNMP_OP_GET 131 
#define  SNMP_OP_GETNEXT 130 
#define  SNMP_OP_ROLLBACK 129 
#define  SNMP_OP_SET 128 
 int /*<<< orphan*/  TRUTH_GET (int) ; 
 int /*<<< orphan*/  TRUTH_OK (int) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  asn_slice_oid (struct asn_oid*,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  index_append (TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  index_decode (TYPE_3__*,int,int,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  lsock_func ; 
 int /*<<< orphan*/  my_trans ; 
 int /*<<< orphan*/  oid_begemotSnmpdLocalPortTable ; 
 scalar_t__ snmp_dep_lookup (struct snmp_context*,int /*<<< orphan*/ *,struct asn_oid*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ trans_find_port (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 scalar_t__ trans_next_port (int /*<<< orphan*/ ,TYPE_3__*,int) ; 

int
op_lsock_port(struct snmp_context *ctx, struct snmp_value *value,
    u_int sub, u_int iidx, enum snmp_op op)
{
	asn_subid_t which = value->var.subs[sub-1];
	struct lsock_port *p;
	u_char *name;
	size_t namelen;
	struct lsock_dep *ld;
	struct asn_oid didx;

	switch (op) {

	  case SNMP_OP_GETNEXT:
		if ((p = (struct lsock_port *)trans_next_port(my_trans,
		    &value->var, sub)) == NULL)
			return (SNMP_ERR_NOSUCHNAME);
		index_append(&value->var, sub, &p->tport.index);
		break;

	  case SNMP_OP_GET:
		if ((p = (struct lsock_port *)trans_find_port(my_trans,
		    &value->var, sub)) == NULL)
			return (SNMP_ERR_NOSUCHNAME);
		break;

	  case SNMP_OP_SET:
		p = (struct lsock_port *)trans_find_port(my_trans,
		    &value->var, sub);

		if (index_decode(&value->var, sub, iidx, &name, &namelen))
			return (SNMP_ERR_NO_CREATION);

		asn_slice_oid(&didx, &value->var, sub, value->var.len);
		if ((ld = (struct lsock_dep *)(void *)snmp_dep_lookup(ctx,
		    &oid_begemotSnmpdLocalPortTable, &didx, sizeof(*ld),
		    lsock_func)) == NULL) {
			free(name);
			return (SNMP_ERR_GENERR);
		}

		if (ld->path == NULL) {
			ld->path = name;
			ld->pathlen = namelen;
		} else {
			free(name);
		}
		ld->port = p;

		switch (which) {

		  case LEAF_begemotSnmpdLocalPortStatus:
			if (ld->set & LD_STATUS)
				return (SNMP_ERR_INCONS_VALUE);
			if (!TRUTH_OK(value->v.integer))
				return (SNMP_ERR_WRONG_VALUE);

			ld->status = TRUTH_GET(value->v.integer);
			ld->set |= LD_STATUS;
			break;

		  case LEAF_begemotSnmpdLocalPortType:
			if (ld->set & LD_TYPE)
				return (SNMP_ERR_INCONS_VALUE);
			if (value->v.integer < 1 || value->v.integer > 4)
				return (SNMP_ERR_WRONG_VALUE);

			ld->type = value->v.integer;
			ld->set |= LD_TYPE;
			break;
		}
		return (SNMP_ERR_NOERROR);

	  case SNMP_OP_ROLLBACK:
	  case SNMP_OP_COMMIT:
		return (SNMP_ERR_NOERROR);

	  default:
		abort();
	}

	/*
	 * Come here to fetch the value
	 */
	switch (which) {

	  case LEAF_begemotSnmpdLocalPortStatus:
		value->v.integer = 1;
		break;

	  case LEAF_begemotSnmpdLocalPortType:
		value->v.integer = p->type;
		break;

	  default:
		abort();
	}

	return (SNMP_ERR_NOERROR);
}