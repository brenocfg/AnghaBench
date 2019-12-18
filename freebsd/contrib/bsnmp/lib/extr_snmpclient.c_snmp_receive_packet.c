#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct timeval {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_6__ {int /*<<< orphan*/  engine_boots; int /*<<< orphan*/  engine_time; } ;
struct snmp_pdu {TYPE_3__ engine; TYPE_3__ user; } ;
struct asn_buf {int asn_len; int /*<<< orphan*/ * asn_ptr; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_7__ {int /*<<< orphan*/  engine_boots; int /*<<< orphan*/  engine_time; } ;
struct TYPE_5__ {scalar_t__ security_model; TYPE_4__ engine; scalar_t__ dump_pdus; TYPE_4__ user; int /*<<< orphan*/  fd; int /*<<< orphan*/  rxbuflen; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EPIPE ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int SNMP_CODE_OK ; 
 scalar_t__ SNMP_SECMODEL_USM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVTIMEO ; 
 int /*<<< orphan*/ * calloc (int,int /*<<< orphan*/ ) ; 
 int errno ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*,int*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  memset (struct snmp_pdu*,int /*<<< orphan*/ ,int) ; 
 int recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seterr (TYPE_1__*,char*,...) ; 
 int setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*,int) ; 
 TYPE_1__ snmp_client ; 
 int snmp_pdu_decode (struct asn_buf*,struct snmp_pdu*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snmp_pdu_dump (struct snmp_pdu*) ; 
 int /*<<< orphan*/  snmp_pdu_init_secparams (struct snmp_pdu*) ; 
 int strerror (int) ; 

__attribute__((used)) static int
snmp_receive_packet(struct snmp_pdu *pdu, struct timeval *tv)
{
	int dopoll, setpoll;
	int flags;
	int saved_errno;
	u_char *buf;
	int ret;
	struct asn_buf abuf;
	int32_t ip;
#ifdef bsdi
	int optlen;
#else
	socklen_t optlen;
#endif

	if ((buf = calloc(1, snmp_client.rxbuflen)) == NULL) {
		seterr(&snmp_client, "%s", strerror(errno));
		return (-1);
	}
	dopoll = setpoll = 0;
	flags = 0;
	if (tv != NULL) {
		/* poll or timeout */
		if (tv->tv_sec != 0 || tv->tv_usec != 0) {
			/* wait with timeout */
			if (setsockopt(snmp_client.fd, SOL_SOCKET, SO_RCVTIMEO,
			    tv, sizeof(*tv)) == -1) {
				seterr(&snmp_client, "setsockopt: %s",
				    strerror(errno));
				free(buf);
				return (-1);
			}
			optlen = sizeof(*tv);
			if (getsockopt(snmp_client.fd, SOL_SOCKET, SO_RCVTIMEO,
			    tv, &optlen) == -1) {
				seterr(&snmp_client, "getsockopt: %s",
				    strerror(errno));
				free(buf);
				return (-1);
			}
			/* at this point tv_sec and tv_usec may appear
			 * as 0. This happens for timeouts lesser than
			 * the clock granularity. The kernel rounds these to
			 * 0 and this would result in a blocking receive.
			 * Instead of an else we check tv_sec and tv_usec
			 * again below and if this rounding happens,
			 * switch to a polling receive. */
		}
		if (tv->tv_sec == 0 && tv->tv_usec == 0) {
			/* poll */
			dopoll = 1;
			if ((flags = fcntl(snmp_client.fd, F_GETFL, 0)) == -1) {
				seterr(&snmp_client, "fcntl: %s",
				    strerror(errno));
				free(buf);
				return (-1);
			}
			if (!(flags & O_NONBLOCK)) {
				setpoll = 1;
				flags |= O_NONBLOCK;
				if (fcntl(snmp_client.fd, F_SETFL, flags) == -1) {
					seterr(&snmp_client, "fcntl: %s",
					    strerror(errno));
					free(buf);
					return (-1);
				}
			}
		}
	}
	ret = recv(snmp_client.fd, buf, snmp_client.rxbuflen, 0);
	saved_errno = errno;
	if (tv != NULL) {
		if (dopoll) {
			if (setpoll) {
				flags &= ~O_NONBLOCK;
				(void)fcntl(snmp_client.fd, F_SETFL, flags);
			}
		} else {
			tv->tv_sec = 0;
			tv->tv_usec = 0;
			(void)setsockopt(snmp_client.fd, SOL_SOCKET, SO_RCVTIMEO,
			    tv, sizeof(*tv));
		}
	}
	if (ret == -1) {
		free(buf);
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return (0);
		seterr(&snmp_client, "recv: %s", strerror(saved_errno));
		return (-1);
	}
	if (ret == 0) {
		/* this happens when we have a streaming socket and the
		 * remote side has closed it */
		free(buf);
		seterr(&snmp_client, "recv: socket closed by peer");
		errno = EPIPE;
		return (-1);
	}

	abuf.asn_ptr = buf;
	abuf.asn_len = ret;

	memset(pdu, 0, sizeof(*pdu));
	if (snmp_client.security_model == SNMP_SECMODEL_USM) {
		memcpy(&pdu->engine, &snmp_client.engine, sizeof(pdu->engine));
		memcpy(&pdu->user, &snmp_client.user, sizeof(pdu->user));
		snmp_pdu_init_secparams(pdu);
	}

	if (SNMP_CODE_OK != (ret = snmp_pdu_decode(&abuf, pdu, &ip))) {
		seterr(&snmp_client, "snmp_decode_pdu: failed %d", ret);
		free(buf);
		return (-1);
	}

	free(buf);
	if (snmp_client.dump_pdus)
		snmp_pdu_dump(pdu);

	snmp_client.engine.engine_time = pdu->engine.engine_time;
	snmp_client.engine.engine_boots = pdu->engine.engine_boots;

	return (+1);
}