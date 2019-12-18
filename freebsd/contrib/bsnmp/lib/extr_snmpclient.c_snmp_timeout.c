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
struct sent_pdu {scalar_t__ retrycount; int /*<<< orphan*/  timeout_id; int /*<<< orphan*/  pdu; int /*<<< orphan*/  reqid; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {scalar_t__ retries; int /*<<< orphan*/  timeout; int /*<<< orphan*/  (* timeout_start ) (int /*<<< orphan*/ *,void (*) (void*),struct sent_pdu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct sent_pdu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  free (struct sent_pdu*) ; 
 TYPE_1__ snmp_client ; 
 int /*<<< orphan*/  snmp_send_packet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,void (*) (void*),struct sent_pdu*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
snmp_timeout(void * listentry_ptr)
{
	struct sent_pdu *listentry = listentry_ptr;

#if 0
	warnx("snmp request %i timed out, attempt (%i/%i)",
	    listentry->reqid, listentry->retrycount, snmp_client.retries);
#endif

	listentry->retrycount++;
	if (listentry->retrycount > snmp_client.retries) {
		/* there is no answer at all */
		LIST_REMOVE(listentry, entries);
		listentry->callback(listentry->pdu, NULL, listentry->arg);
		free(listentry);
	} else {
		/* try again */
		/* new request with new request ID */
		listentry->reqid = snmp_send_packet(listentry->pdu);
		listentry->timeout_id =
		    snmp_client.timeout_start(&snmp_client.timeout,
		    snmp_timeout, listentry);
	}
}