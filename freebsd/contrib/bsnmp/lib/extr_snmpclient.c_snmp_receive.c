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
typedef  int /*<<< orphan*/  tv ;
struct timeval {int dummy; } ;
struct snmp_pdu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct snmp_pdu*) ; 
 struct snmp_pdu* malloc (int) ; 
 int /*<<< orphan*/  memset (struct timeval*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  seterr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snmp_client ; 
 int snmp_deliver_packet (struct snmp_pdu*) ; 
 int /*<<< orphan*/  snmp_pdu_free (struct snmp_pdu*) ; 
 int snmp_receive_packet (struct snmp_pdu*,struct timeval*) ; 

int
snmp_receive(int blocking)
{
	int ret;

	struct timeval tv;
	struct snmp_pdu * resp;

	memset(&tv, 0, sizeof(tv));

	resp = malloc(sizeof(struct snmp_pdu));
	if (resp == NULL) {
		seterr(&snmp_client, "no memory for returning PDU");
		return (-1) ;
	}

	if ((ret = snmp_receive_packet(resp, blocking ? NULL : &tv)) <= 0) {
		free(resp);
		return (ret);
	}
	ret = snmp_deliver_packet(resp);
	snmp_pdu_free(resp);
	free(resp);
	return (ret);
}