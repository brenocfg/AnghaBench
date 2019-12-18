#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct table {int dummy; } ;
struct tabwork {int first; int /*<<< orphan*/  pdu; scalar_t__ last_change; void* arg; int /*<<< orphan*/  callback; struct table worklist; struct table* table; scalar_t__ iter; struct snmp_table const* descr; } ;
struct snmp_table {int dummy; } ;
typedef  int /*<<< orphan*/  snmp_table_cb_f ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (struct table*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct tabwork*) ; 
 struct tabwork* malloc (int) ; 
 int /*<<< orphan*/  seterr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmp_client ; 
 int snmp_pdu_send (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct tabwork*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_cb ; 
 int /*<<< orphan*/  table_init_pdu (struct snmp_table const*,int /*<<< orphan*/ *) ; 

int
snmp_table_fetch_async(const struct snmp_table *descr, void *list,
    snmp_table_cb_f func, void *arg)
{
	struct tabwork *work;

	if ((work = malloc(sizeof(*work))) == NULL) {
		seterr(&snmp_client, "%s", strerror(errno));
		return (-1);
	}

	work->descr = descr;
	work->table = (struct table *)list;
	work->iter = 0;
	TAILQ_INIT(work->table);
	TAILQ_INIT(&work->worklist);

	work->callback = func;
	work->arg = arg;

	/*
	 * Start by sending the first PDU
	 */
	work->first = 1;
	work->last_change = 0;
	table_init_pdu(descr, &work->pdu);

	if (snmp_pdu_send(&work->pdu, table_cb, work) == -1) {
		free(work);
		work = NULL;
		return (-1);
	}
	return (0);
}