#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct tabwork {scalar_t__ last_change; scalar_t__ iter; TYPE_2__* descr; scalar_t__ first; } ;
struct TYPE_10__ {int len; scalar_t__* subs; } ;
struct TYPE_8__ {scalar_t__ uint32; } ;
typedef  struct snmp_value {scalar_t__ syntax; TYPE_3__ var; TYPE_1__ v; } const snmp_value ;
struct snmp_pdu {scalar_t__ error_status; int error_index; int nbindings; struct snmp_value const* bindings; } ;
struct entry {int dummy; } ;
struct TYPE_12__ {int len; } ;
struct TYPE_11__ {scalar_t__ version; } ;
struct TYPE_9__ {scalar_t__ max_iter; TYPE_6__ table; TYPE_6__ last_change; } ;

/* Variables and functions */
 scalar_t__ SNMP_ERR_NOERROR ; 
 scalar_t__ SNMP_ERR_NOSUCHNAME ; 
 scalar_t__ SNMP_SYNTAX_ENDOFMIBVIEW ; 
 scalar_t__ SNMP_SYNTAX_TIMETICKS ; 
 scalar_t__ SNMP_V1 ; 
 int /*<<< orphan*/  asn_is_suboid (TYPE_6__*,TYPE_3__*) ; 
 int /*<<< orphan*/  seterr (TYPE_4__*,char*,...) ; 
 TYPE_4__ snmp_client ; 
 struct entry* table_find (struct tabwork*,TYPE_3__*) ; 
 int /*<<< orphan*/  table_free (struct tabwork*,int) ; 
 scalar_t__ table_value (TYPE_2__*,struct entry*,struct snmp_value const*) ; 

__attribute__((used)) static int
table_check_response(struct tabwork *work, const struct snmp_pdu *resp)
{
	const struct snmp_value *b;
	struct entry *e;

	if (resp->error_status != SNMP_ERR_NOERROR) {
		if (snmp_client.version == SNMP_V1 &&
		    resp->error_status == SNMP_ERR_NOSUCHNAME &&
		    resp->error_index ==
		    (work->descr->last_change.len == 0) ? 1 : 2)
			/* EOT */
			return (0);
		/* Error */
		seterr(&snmp_client, "error fetching table: status=%d index=%d",
		    resp->error_status, resp->error_index);
		return (-1);
	}

	for (b = resp->bindings; b < resp->bindings + resp->nbindings; b++) {
		if (work->descr->last_change.len != 0 && b == resp->bindings) {
			if (!asn_is_suboid(&work->descr->last_change, &b->var) ||
			    b->var.len != work->descr->last_change.len + 1 ||
			    b->var.subs[work->descr->last_change.len] != 0) {
				seterr(&snmp_client,
				    "last_change: bad response");
				return (-1);
			}
			if (b->syntax != SNMP_SYNTAX_TIMETICKS) {
				seterr(&snmp_client,
				    "last_change: bad syntax %u", b->syntax);
				return (-1);
			}
			if (work->first) {
				work->last_change = b->v.uint32;
				work->first = 0;

			} else if (work->last_change != b->v.uint32) {
				if (++work->iter >= work->descr->max_iter) {
					seterr(&snmp_client,
					    "max iteration count exceeded");
					return (-1);
				}
				table_free(work, 1);
				return (-2);
			}

			continue;
		}
		if (!asn_is_suboid(&work->descr->table, &b->var) ||
		    b->syntax == SNMP_SYNTAX_ENDOFMIBVIEW)
			return (0);

		if ((e = table_find(work, &b->var)) == NULL)
			return (-1);
		if (table_value(work->descr, e, b))
			return (-1);
	}
	return (+1);
}