#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nbindings; TYPE_1__* bindings; } ;
struct table {int dummy; } ;
struct tabwork {int first; TYPE_3__ pdu; scalar_t__ last_change; int /*<<< orphan*/ * arg; int /*<<< orphan*/ * callback; struct table worklist; struct table* table; scalar_t__ iter; struct snmp_table const* descr; } ;
struct snmp_table {int dummy; } ;
struct snmp_pdu {int nbindings; TYPE_2__* bindings; } ;
struct TYPE_6__ {int /*<<< orphan*/  var; } ;
struct TYPE_5__ {int /*<<< orphan*/  var; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (struct table*) ; 
 scalar_t__ snmp_dialog (TYPE_3__*,struct snmp_pdu*) ; 
 int /*<<< orphan*/  snmp_pdu_free (struct snmp_pdu*) ; 
 int table_check_cons (struct tabwork*) ; 
 int table_check_response (struct tabwork*,struct snmp_pdu*) ; 
 int /*<<< orphan*/  table_free (struct tabwork*,int) ; 
 int /*<<< orphan*/  table_init_pdu (struct snmp_table const*,TYPE_3__*) ; 

int
snmp_table_fetch(const struct snmp_table *descr, void *list)
{
	struct snmp_pdu resp;
	struct tabwork work;
	int ret;

	work.descr = descr;
	work.table = (struct table *)list;
	work.iter = 0;
	TAILQ_INIT(work.table);
	TAILQ_INIT(&work.worklist);
	work.callback = NULL;
	work.arg = NULL;

  again:
	/*
	 * We come to this label when the code detects that the table
	 * has changed while fetching it.
	 */
	work.first = 1;
	work.last_change = 0;
	table_init_pdu(descr, &work.pdu);

	for (;;) {
		if (snmp_dialog(&work.pdu, &resp)) {
			table_free(&work, 1);
			return (-1);
		}
		if ((ret = table_check_response(&work, &resp)) == 0) {
			snmp_pdu_free(&resp);
			break;
		}
		if (ret == -1) {
			snmp_pdu_free(&resp);
			table_free(&work, 1);
			return (-1);
		}
		if (ret == -2) {
			snmp_pdu_free(&resp);
			goto again;
		}

		work.pdu.bindings[work.pdu.nbindings - 1].var =
		    resp.bindings[resp.nbindings - 1].var;

		snmp_pdu_free(&resp);
	}

	if ((ret = table_check_cons(&work)) == -1) {
		table_free(&work, 1);
		return (-1);
	}
	if (ret == -2) {
		table_free(&work, 1);
		goto again;
	}
	/*
	 * Free index list
	 */
	table_free(&work, 0);
	return (0);
}