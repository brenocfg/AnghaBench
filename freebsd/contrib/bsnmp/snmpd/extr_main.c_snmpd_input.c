#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct tport {TYPE_5__* transport; int /*<<< orphan*/  index; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct snmp_value {int dummy; } ;
struct snmp_pdu {scalar_t__ type; scalar_t__ version; } ;
struct port_input {scalar_t__ length; int /*<<< orphan*/  peerlen; TYPE_4__* peer; int /*<<< orphan*/  buf; scalar_t__ priv; scalar_t__ cred; scalar_t__ stream; int /*<<< orphan*/  consumed; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  enum snmpd_proxy_err { ____Placeholder_snmpd_proxy_err } snmpd_proxy_err ;
typedef  enum snmpd_input_err { ____Placeholder_snmpd_input_err } snmpd_input_err ;
typedef  int /*<<< orphan*/  client ;
struct TYPE_17__ {scalar_t__ private; TYPE_2__* owner; } ;
struct TYPE_16__ {scalar_t__ auth_traps; } ;
struct TYPE_15__ {int /*<<< orphan*/  silentDrops; int /*<<< orphan*/  inBadCommunityUses; int /*<<< orphan*/  inBadPduTypes; int /*<<< orphan*/  inBadCommunityNames; int /*<<< orphan*/  proxyDrops; } ;
struct TYPE_14__ {TYPE_3__* vtab; } ;
struct TYPE_13__ {scalar_t__ sa_family; } ;
struct TYPE_12__ {int (* recv ) (struct tport*,struct port_input*) ;int (* send ) (struct tport*,int /*<<< orphan*/ *,size_t,TYPE_4__*,int /*<<< orphan*/ ) ;int (* send2 ) (struct tport*,int /*<<< orphan*/ *,size_t,struct port_input*) ;} ;
struct TYPE_11__ {TYPE_1__* config; } ;
struct TYPE_10__ {int (* proxy ) (struct snmp_pdu*,TYPE_5__*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 scalar_t__ AF_LOCAL ; 
 scalar_t__ COMM_READ ; 
 scalar_t__ COMM_WRITE ; 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  RQ_CLIENT_ADDR ; 
 int SNMPD_INPUT_BAD_COMM ; 
 int SNMPD_INPUT_FAILED ; 
 int SNMPD_INPUT_OK ; 
 int SNMPD_INPUT_TRUNC ; 
#define  SNMPD_PROXY_BADCOMM 132 
#define  SNMPD_PROXY_BADCOMMUSE 131 
#define  SNMPD_PROXY_DROP 130 
#define  SNMPD_PROXY_OK 129 
#define  SNMPD_PROXY_REJ 128 
 scalar_t__ SNMP_PDU_RESPONSE ; 
 scalar_t__ SNMP_PDU_SET ; 
 scalar_t__ SNMP_PDU_TRAP ; 
 scalar_t__ SNMP_PDU_TRAP2 ; 
 scalar_t__ SNMP_V3 ; 
 int /*<<< orphan*/ * buf_alloc (int) ; 
 scalar_t__ buf_size (int /*<<< orphan*/ ) ; 
 TYPE_9__* comm ; 
 int /*<<< orphan*/  eval_client (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ hosts_access (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * inet_ntop (scalar_t__,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  oid_authenticationFailure ; 
 int /*<<< orphan*/  req ; 
 int /*<<< orphan*/  request_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmp_input_consume (struct port_input*) ; 
 int snmp_input_finish (struct snmp_pdu*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,size_t*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int snmp_input_start (int /*<<< orphan*/ ,scalar_t__,char*,struct snmp_pdu*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snmp_pdu_free (struct snmp_pdu*) ; 
 int /*<<< orphan*/  snmp_send_trap (int /*<<< orphan*/ *,struct snmp_value*) ; 
 TYPE_8__ snmpd ; 
 TYPE_7__ snmpd_stats ; 
 int stub1 (struct tport*,struct port_input*) ; 
 int stub2 (struct snmp_pdu*,TYPE_5__*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int stub3 (struct tport*,int /*<<< orphan*/ *,size_t,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int stub4 (struct tport*,int /*<<< orphan*/ *,size_t,struct port_input*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

int
snmpd_input(struct port_input *pi, struct tport *tport)
{
	u_char *sndbuf;
	size_t sndlen;
	struct snmp_pdu pdu;
	enum snmpd_input_err ierr, ferr;
	enum snmpd_proxy_err perr;
	ssize_t ret, slen;
	int32_t vi;
#ifdef USE_TCPWRAPPERS
	char client[INET6_ADDRSTRLEN];
#endif

	ret = tport->transport->vtab->recv(tport, pi);
	if (ret == -1)
		return (-1);

#ifdef USE_TCPWRAPPERS
	/*
	 * In case of AF_INET{6} peer, do hosts_access(5) check.
	 */
	if (pi->peer->sa_family != AF_LOCAL &&
	    inet_ntop(pi->peer->sa_family,
	    &((const struct sockaddr_in *)(const void *)pi->peer)->sin_addr,
	    client, sizeof(client)) != NULL) {
		request_set(&req, RQ_CLIENT_ADDR, client, 0);
		if (hosts_access(&req) == 0) {
			syslog(LOG_ERR, "refused connection from %.500s",
			    eval_client(&req));
			return (-1);
		}
	} else if (pi->peer->sa_family != AF_LOCAL)
		syslog(LOG_ERR, "inet_ntop(): %m");
#endif

	/*
	 * Handle input
	 */
	ierr = snmp_input_start(pi->buf, pi->length, "SNMP", &pdu, &vi,
	    &pi->consumed);
	if (ierr == SNMPD_INPUT_TRUNC) {
		/* need more bytes. This is ok only for streaming transports.
		 * but only if we have not reached bufsiz yet. */
		if (pi->stream) {
			if (pi->length == buf_size(0)) {
				snmpd_stats.silentDrops++;
				return (-1);
			}
			return (0);
		}
		snmpd_stats.silentDrops++;
		return (-1);
	}

	/* can't check for bad SET pdus here, because a proxy may have to
	 * check the access first. We don't want to return an error response
	 * to a proxy PDU with a wrong community */
	if (ierr == SNMPD_INPUT_FAILED) {
		/* for streaming transports this is fatal */
		if (pi->stream)
			return (-1);
		snmp_input_consume(pi);
		return (0);
	}
	if (ierr == SNMPD_INPUT_BAD_COMM) {
		snmp_input_consume(pi);
		return (0);
	}

	/*
	 * If that is a module community and the module has a proxy function,
	 * the hand it over to the module.
	 */
	if (comm != NULL && comm->owner != NULL &&
	    comm->owner->config->proxy != NULL) {
		perr = (*comm->owner->config->proxy)(&pdu, tport->transport,
		    &tport->index, pi->peer, pi->peerlen, ierr, vi,
		    !pi->cred || pi->priv);

		switch (perr) {

		  case SNMPD_PROXY_OK:
			snmp_input_consume(pi);
			return (0);

		  case SNMPD_PROXY_REJ:
			break;

		  case SNMPD_PROXY_DROP:
			snmp_input_consume(pi);
			snmp_pdu_free(&pdu);
			snmpd_stats.proxyDrops++;
			return (0);

		  case SNMPD_PROXY_BADCOMM:
			snmp_input_consume(pi);
			snmp_pdu_free(&pdu);
			snmpd_stats.inBadCommunityNames++;
			if (snmpd.auth_traps)
				snmp_send_trap(&oid_authenticationFailure,
				    (struct snmp_value *)NULL);
			return (0);

		  case SNMPD_PROXY_BADCOMMUSE:
			snmp_input_consume(pi);
			snmp_pdu_free(&pdu);
			snmpd_stats.inBadCommunityUses++;
			if (snmpd.auth_traps)
				snmp_send_trap(&oid_authenticationFailure,
				    (struct snmp_value *)NULL);
			return (0);
		}
	}

	/*
	 * Check type
	 */
	if (pdu.type == SNMP_PDU_RESPONSE ||
	    pdu.type == SNMP_PDU_TRAP ||
	    pdu.type == SNMP_PDU_TRAP2) {
		snmpd_stats.silentDrops++;
		snmpd_stats.inBadPduTypes++;
		snmp_pdu_free(&pdu);
		snmp_input_consume(pi);
		return (0);
	}

	/*
	 * Check community
	 */
	if (pdu.version < SNMP_V3 &&
	    ((pi->cred && !pi->priv && pdu.type == SNMP_PDU_SET) ||
	    (comm != NULL && comm->private != COMM_WRITE &&
            (pdu.type == SNMP_PDU_SET || comm->private != COMM_READ)))) {
		snmpd_stats.inBadCommunityUses++;
		snmp_pdu_free(&pdu);
		snmp_input_consume(pi);
		if (snmpd.auth_traps)
			snmp_send_trap(&oid_authenticationFailure,
			    (struct snmp_value *)NULL);
		return (0);
	}

	/*
	 * Execute it.
	 */
	if ((sndbuf = buf_alloc(1)) == NULL) {
		snmpd_stats.silentDrops++;
		snmp_pdu_free(&pdu);
		snmp_input_consume(pi);
		return (0);
	}
	ferr = snmp_input_finish(&pdu, pi->buf, pi->length,
	    sndbuf, &sndlen, "SNMP", ierr, vi, NULL);

	if (ferr == SNMPD_INPUT_OK) {
		if (tport->transport->vtab->send != NULL)
			slen = tport->transport->vtab->send(tport, sndbuf,
			    sndlen, pi->peer, pi->peerlen);
		else
			slen = tport->transport->vtab->send2(tport, sndbuf,
			    sndlen, pi);
		if (slen == -1)
			syslog(LOG_ERR, "send*: %m");
		else if ((size_t)slen != sndlen)
			syslog(LOG_ERR, "send*: short write %zu/%zu", sndlen,
			    (size_t)slen);
	}

	snmp_pdu_free(&pdu);
	free(sndbuf);
	snmp_input_consume(pi);

	return (0);
}