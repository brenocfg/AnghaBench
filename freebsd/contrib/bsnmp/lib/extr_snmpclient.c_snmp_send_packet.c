#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct snmp_pdu {int request_id; } ;
struct asn_buf {int /*<<< orphan*/ * asn_ptr; int /*<<< orphan*/  asn_len; } ;
typedef  int ssize_t ;
typedef  int int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  fd; scalar_t__ dump_pdus; int /*<<< orphan*/  txbuflen; } ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seterr (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ snmp_client ; 
 int snmp_next_reqid (TYPE_1__*) ; 
 int /*<<< orphan*/  snmp_pdu_dump (struct snmp_pdu*) ; 
 scalar_t__ snmp_pdu_encode (struct snmp_pdu*,struct asn_buf*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
snmp_send_packet(struct snmp_pdu * pdu)
{
	u_char *buf;
	struct asn_buf b;
	ssize_t ret;

	if ((buf = calloc(1, snmp_client.txbuflen)) == NULL) {
		seterr(&snmp_client, "%s", strerror(errno));
		return (-1);
	}

	pdu->request_id = snmp_next_reqid(&snmp_client);

	b.asn_ptr = buf;
	b.asn_len = snmp_client.txbuflen;
	if (snmp_pdu_encode(pdu, &b)) {
		seterr(&snmp_client, "%s", strerror(errno));
		free(buf);
		return (-1);
	}

	if (snmp_client.dump_pdus)
		snmp_pdu_dump(pdu);

	if ((ret = send(snmp_client.fd, buf, b.asn_ptr - buf, 0)) == -1) {
		seterr(&snmp_client, "%s", strerror(errno));
		free(buf);
		return (-1);
	}
	free(buf);

	return (pdu->request_id);
}