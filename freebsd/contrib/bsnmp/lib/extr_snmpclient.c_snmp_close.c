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
struct sent_pdu {int /*<<< orphan*/ * timeout_id; } ;
struct TYPE_2__ {int fd; char* local_path; struct sent_pdu* cport; struct sent_pdu* chost; int /*<<< orphan*/  (* timeout_stop ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct sent_pdu* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct sent_pdu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  free (struct sent_pdu*) ; 
 int /*<<< orphan*/  remove (char*) ; 
 int /*<<< orphan*/  sent_pdus ; 
 TYPE_1__ snmp_client ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void
snmp_close(void)
{
	struct sent_pdu *p1;

	if (snmp_client.fd != -1) {
		(void)close(snmp_client.fd);
		snmp_client.fd = -1;
		if (snmp_client.local_path[0] != '\0')
			(void)remove(snmp_client.local_path);
	}
	while(!LIST_EMPTY(&sent_pdus)){
		p1 = LIST_FIRST(&sent_pdus);
		if (p1->timeout_id != NULL)
			snmp_client.timeout_stop(p1->timeout_id);
		LIST_REMOVE(p1, entries);
		free(p1);
	}
	free(snmp_client.chost);
	free(snmp_client.cport);
}